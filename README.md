# ⚡ EnerTrack

Sistema IoT de Monitoreo Energético en Tiempo Real con ESP32, MQTT e InfluxDB

---

## 📋 Descripción

EnerTrack es una plataforma completa de monitoreo energético que combina hardware ESP32 con una interfaz web moderna. Permite monitorear múltiples puntos de medición eléctrica en tiempo real, visualizar datos históricos, configurar alertas personalizadas por Telegram y analizar patrones de consumo.

**Características principales:**
- 📊 Monitoreo en tiempo real de tensión, corriente, potencia, factor de potencia y frecuencia
- 📈 Visualización de datos históricos (hora, día, mes, año)
- 🔔 Alertas automáticas por Telegram cuando se superan umbrales
- 🔒 Comunicación segura MQTT con SSL/TLS
- 👥 Gestión multiusuario con permisos compartibles
- 📱 Interfaz responsive compatible con móviles

---

## 🏗️ Arquitectura

El sistema está compuesto por los siguientes servicios dockerizados:

```
ESP32 Nodos → MQTT (SSL) → Mosquitto Broker → InfluxDB (series temporales)
                                             ↓
                                    Flask App ← MariaDB (usuarios/config)
                                             ↓
                              Dashboard Web + Telegram Bot
```

**Stack tecnológico:**
- **Backend:** Python 3.11 + Flask + Gunicorn
- **Frontend:** HTML5 + Bootstrap 5 + Chart.js
- **Bases de Datos:** MariaDB + InfluxDB
- **IoT:** ESP32 + MQTT (Mosquitto)
- **Proxy/SSL:** SWAG (Nginx + Let's Encrypt)
- **Contenedores:** Docker + Docker Compose

---

## 🚀 Instalación

### Requisitos previos

- Docker y Docker Compose instalados
- Dominio DuckDNS (gratuito en [duckdns.org](https://www.duckdns.org))
- Bot de Telegram (crear con [@BotFather](https://t.me/botfather))

### Pasos de instalación

**1. Clonar el repositorio**
```bash
git clone https://github.com/ignaciobehler/EnerTrack_V1.0.git
cd EnerTrack_V1.0
```

**2. Configurar variables de entorno**
```bash
cp .env.example .env
nano .env
```

Editar las variables principales:
```bash
MARIADB_ROOT_PASSWORD=tu_password_seguro
MYSQL_PASSWORD=tu_mysql_password
INFLUX_TOKEN=tu_token_influxdb
DOMINIO=tu_subdominio.duckdns.org
enertrackBotToken=tu_token_bot_telegram
```

**3. Generar claves secretas**
```bash
python3 generate_keys.py
```
Copiar las claves generadas en el archivo `.env`

**4. Configurar DuckDNS**

Editar `mosquitto/config/duckdns.ini`:
```ini
dns_duckdns_token=tu_token_duckdns
```

**5. Inicializar base de datos**
```bash
docker network create docker_iot-1_default
docker compose up -d mariadb
sleep 10
docker exec -i mariadb mariadb -u root -p${MARIADB_ROOT_PASSWORD} < schema.sql
```

**6. Iniciar todos los servicios**
```bash
docker compose up -d
```

**7. Configurar InfluxDB**

Acceder a `http://localhost:8086`:
- Crear organización: `IoT`
- Crear bucket: `medidoresEnergia`
- Generar token de API
- Copiar el token a `.env` como `INFLUX_TOKEN`
- Reiniciar: `docker compose restart enertrack`

**8. Acceder a la aplicación**

Abrir navegador en: `https://tu_dominio.duckdns.org`

---

## 🔧 Configuración ESP32

Ejemplo de código Arduino para publicar mediciones:

```cpp
const char* mqtt_server = "tu_dominio.duckdns.org";
const int mqtt_port = 8883;  // MQTTS con SSL
const char* mqtt_user = "enertrack_mqtt";
const char* mqtt_password = "tu_password_mqtt";

// Topics MQTT:
// enertrack/{ESP_ID}/tension
// enertrack/{ESP_ID}/corriente
// enertrack/{ESP_ID}/consumo
// enertrack/{ESP_ID}/fp
// enertrack/{ESP_ID}/frecuencia
```

---

## 📊 Uso

### Primeros pasos

1. Registrarse en la aplicación web
2. Iniciar sesión
3. Ir a "Mis Nodos" y agregar un nuevo nodo con el ESP_ID
4. Configurar umbral de alerta
5. Vincular cuenta de Telegram para recibir alertas

### Visualización de datos

- **Dashboard General:** Vista de todos los nodos
- **Dashboard Individual:** Detalles de un nodo específico
- **Consumo Global:** Análisis comparativo
- **Gráficos por Magnitud:** Histórico detallado

---

## 🛠️ Comandos útiles

```bash
# Ver logs en tiempo real
docker compose logs -f enertrack

# Reiniciar un servicio
docker compose restart enertrack

# Reconstruir después de cambios
docker compose build enertrack
docker compose up -d enertrack

# Detener todo
docker compose down
```

---

## 📁 Estructura del proyecto

```
enertrack/
├── compose.yaml         # Configuración Docker Compose
├── .env                 # Variables de entorno (NO subir a Git)
├── schema.sql           # Esquema de base de datos
├── enertrack/           # Aplicación Flask
│   ├── app.py          # Backend principal
│   ├── telegram_bot.py # Bot de Telegram
│   ├── templates/      # Vistas HTML
│   └── static/         # JS, CSS, imágenes
├── mosquitto/config/   # Configuración MQTT
├── docs/               # Documentación
└── README.md           # Este archivo
```

---

## 🔒 Seguridad

- ✅ Autenticación con hash de contraseñas (Scrypt)
- ✅ Comunicación HTTPS/TLS en todos los servicios
- ✅ MQTT con SSL/TLS (MQTTS)
- ✅ Variables de entorno para secretos
- ✅ Certificados SSL automáticos con Let's Encrypt

---

## 🤝 Contribuir

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crear rama: `git checkout -b feature/nueva-funcionalidad`
3. Commit: `git commit -m 'Add: nueva funcionalidad'`
4. Push: `git push origin feature/nueva-funcionalidad`
5. Abrir Pull Request

Ver [CONTRIBUTING.md](docs/CONTRIBUTING.md) para más detalles.

---

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Ver [LICENSE](LICENSE) para más detalles.

---

## 👥 Autores

- **Ignacio Behler** - [@ignaciobehler](https://github.com/ignaciobehler)
- **Emiliano Lukoski**

---

## 📞 Soporte

- Issues: [GitHub Issues](https://github.com/ignaciobehler/EnerTrack_V1.0/issues)
- Documentación: Ver directorio `/docs`

---

**Hecho con ❤️ para la comunidad IoT**
