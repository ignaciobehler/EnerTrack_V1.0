/******************************************************************************
 *  EnerTrack – Nodo ESP32 + PZEM-004T v3
 *  Versión 1.4-MQTTS-insecure + auto-retry UART  (27 jul 2025)
 *
 *  Ajustes (26 ago 2025):
 *    • Consumo: integración de potencia (trapecio) con muestreo periódico.
 *    • Publicación cada 2 minutos.
 *    • NUEVO: publicación de potencia promedio de la ventana (W) -> "potencia_prom".
 *    • Serial: reemplazo de "→" por "->" para evitar caracteres raros.
 ******************************************************************************/

/* ---------------- Bibliotecas ---------------- */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>
#include <time.h>

/* ---------------- Credenciales ---------------- */
const char* WIFI_SSID  = "Your_SSID_Name";
const char* WIFI_PASS  = "Your_Password";

const char* MQTT_HOST  = "Your_MQTT_Server";
const uint16_t MQTT_PORT = Your_MQTT_Port;
const char* MQTT_USER  = "Your_MQTT_User";
const char* MQTT_PASS  = "Your_MQTT_Password";

/* ---------------- UART2 PZEM ---------------- */
#define PZEM_RX_PIN 16   // GPIO16 (RX2)
#define PZEM_TX_PIN 17   // GPIO17 (TX2)

/* ---------------- Instancias ---------------- */
WiFiClientSecure  net;
PubSubClient      client(net);
PZEM004Tv30       pzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);

/* ---------------- Variables ---------------- */
char esp_id[9] = {0};
static float last_energy = 0.0;
static bool first_cycle = true;          // se mantiene por compatibilidad
static uint8_t err_consec = 0;           // errores seguidos de lectura

/* Publicación cada 2 minutos */
const uint32_t PUB_INTERVAL_MS = 120000; // 2 min
uint32_t last_pub = 0;

/* -------- Integración de potencia --------
   - Muestreo de potencia cada SAMPLE_INTERVAL_MS
   - Se acumula energía en watt-seconds (Ws) y luego se pasa a kWh
*/
const uint32_t SAMPLE_INTERVAL_MS = 2000; // 2 s
uint32_t last_sample = 0;
uint32_t window_start_ms = 0;
static double acc_energy_ws = 0.0;        // acumulador de energía (Ws)
static float  prevP = NAN;                // potencia anterior válida

/* ===================================================================== */
/* ---------------- Funciones auxiliares ---------------- */

void connectWiFi()
{
    Serial.printf("[WiFi] Conectando a \"%s\" ...\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print('.'); }
    Serial.println();
    Serial.printf("[WiFi] Conectado. IP: %s  RSSI: %d dBm\n",
                  WiFi.localIP().toString().c_str(), WiFi.RSSI());

    /* Hora para TLS */
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("[NTP] Esperando hora... ");
    time_t now = time(nullptr);
    while (now < 1700000000) { delay(500); Serial.print('.'); now = time(nullptr); }
    Serial.printf(" ok (%s", ctime(&now));
}

void connectMQTT()
{
    Serial.printf("[MQTT] Conectando a %s:%u ...\n", MQTT_HOST, MQTT_PORT);
    net.setTimeout(15000);
    while (!client.connected()) {
        if (client.connect(esp_id, MQTT_USER, MQTT_PASS)) {
            Serial.println("[MQTT] Conexion establecida.");
            break;
        }
        Serial.printf("[MQTT] Error rc=%d. Reintento en 2 s...\n", client.state());
        delay(2000);
    }
}

void publishValue(const char* magn, float val, uint8_t prec)
{
    char topic[64], payload[16];
    snprintf(topic, sizeof(topic), "enertrack/%s/%s", esp_id, magn);
    dtostrf(val, 0, prec, payload);
    client.publish(topic, payload, false);
    Serial.printf("[PUB] %s -> %s\n", topic, payload);  // ASCII para evitar basura
}

/* Muestrea potencia y acumula energía (método del trapecio) */
void integratePower()
{
    uint32_t now = millis();
    if (now - last_sample < SAMPLE_INTERVAL_MS) return;

    float P = pzem.power(); // Watts
    if (isnan(P)) {
        err_consec++;
        Serial.printf("[WARN] Potencia invalida en muestreo (%u/3)\n", err_consec);
        if (err_consec >= 3) {
            Serial.println("[INFO] Reinicializando UART2 y PZEM...");
            Serial2.end();
            delay(100);
            Serial2.begin(9600, SERIAL_8N1, PZEM_RX_PIN, PZEM_TX_PIN);
            pzem = PZEM004Tv30(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);
            err_consec = 0;
            first_cycle = true;
            prevP = NAN;
        }
        // avanzamos el reloj de muestreo para evitar dt enormes
        last_sample = now;
        return;
    }

    // lectura válida
    if (!isnan(prevP)) {
        double dt = (now - last_sample) / 1000.0;  // s
        acc_energy_ws += 0.5 * (prevP + P) * dt;   // trapecio: Ws
    }
    prevP = P;
    last_sample = now;
    err_consec = 0;
}

/* ===================================================================== */
/* ---------------- setup() ---------------- */

void setup()
{
    Serial.begin(115200);
    delay(50);
    Serial.println("\n============== EnerTrack Nodo ESP32 ==============");

    sprintf(esp_id, "%08X", (uint32_t)ESP.getEfuseMac());
    Serial.printf("ESPID: %s\n", esp_id);

    connectWiFi();
    net.setInsecure();                     // TLS sin verificacion de CA
    client.setServer(MQTT_HOST, MQTT_PORT);
    connectMQTT();
    last_sample = millis();                // arranque integrador
    window_start_ms = last_sample;
    Serial.println("=================================================\n");
}

/* ===================================================================== */
/* ---------------- loop() ---------------- */

void loop()
{
    if (!client.connected()) connectMQTT();
    client.loop();

    /* Integrar potencia con muestreo periódico */
    integratePower();

    /* Publicación cada PUB_INTERVAL_MS */
    if (millis() - last_pub < PUB_INTERVAL_MS) return;
    last_pub = millis();

    /* ---------- Lecturas "instantáneas" para publicar ---------- */
    float V  = pzem.voltage();
    float I  = pzem.current();
    float P  = pzem.power();
    float E  = pzem.energy();
    float F  = pzem.frequency();
    float PF = pzem.pf();

    bool invalid = isnan(V) || isnan(I) || isnan(P) ||
                   isnan(E) || isnan(F) || isnan(PF);

    if (invalid) {
        err_consec++;
        Serial.printf("[WARN] Lectura invalida en publicacion (%u/3)\n", err_consec);

        if (err_consec >= 3) {
            Serial.println("[INFO] Reinicializando UART2 y PZEM...");
            Serial2.end();
            delay(100);
            Serial2.begin(9600, SERIAL_8N1, PZEM_RX_PIN, PZEM_TX_PIN);
            pzem = PZEM004Tv30(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);
            err_consec = 0;
            first_cycle = true;
            prevP = NAN;
        }
        return; // omite esta publicación
    }

    err_consec = 0; // lectura válida

    /* ---------- Consumo integrado y potencia promedio ----------
       acc_energy_ws está en watt-seconds (Ws).
       1 kWh = 3.600.000 Ws
    */
    double window_secs = (double)(millis() - window_start_ms) / 1000.0;
    if (window_secs < 0.1) window_secs = 0.1; // guardarrail

    float delta_kWh = (float)(acc_energy_ws / 3600000.0);
    if (delta_kWh < 0) delta_kWh = 0.0f;

    float avg_W = (float)(acc_energy_ws / window_secs);

    /* Reiniciar ventana de integración */
    acc_energy_ws = 0.0;
    prevP = NAN;                 // fuerza nuevo arranque de trapecio
    last_sample = millis();      // referencia de muestreo
    window_start_ms = last_sample;

    /* ---------- Publicaciones ---------- */
    publishValue("tension",       V, 1);
    publishValue("corriente",     I, 2);
    publishValue("fp",            PF, 2);
    publishValue("frecuencia",    F, 2);
    publishValue("potencia_prom", avg_W, 1);   // NUEVO: potencia promedio (W)
    publishValue("consumo",       delta_kWh, 4);  // consumo integrado (kWh/ventana)
    publishValue("energy_raw",    E, 3);          // registro del PZEM
}
