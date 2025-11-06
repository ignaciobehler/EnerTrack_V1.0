# 🔋 ENERTRACK - Plataforma de Monitoreo Energético

Plataforma web completa para monitorear y analizar el consumo eléctrico en tiempo real mediante medidores inteligentes basados en ESP32.

## 📋 Características

- ✅ Gestión de usuarios y nodos ESP32
- ✅ Monitoreo en tiempo real vía MQTT/MQTTS
- ✅ Dashboards interactivos con Chart.js
- ✅ Base de datos relacional (MariaDB) y series temporales (InfluxDB)
- ✅ Alertas automáticas por Telegram
- ✅ Análisis de consumo por hora/día/mes/año
- ✅ Tema claro/oscuro
- ✅ Proxy inverso con SSL (Let's Encrypt)

## 🏗️ Arquitectura

```
┌─────────────┐
│   ESP32     │──MQTT──┐
│  Medidores  │        │
└─────────────┘        │
                       ▼
┌──────────────────────────────────────────┐
│           Mosquitto (MQTT Broker)        │
│              Puerto 1883/8883            │
└──────────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────┐
│         EnerTrack (Flask App)            │
│              Puerto 8006                 │
│  ┌────────────┐  ┌─────────────────┐   │
│  │ Telegram   │  │  Worker MQTT    │   │
│  │    Bot     │  │  → InfluxDB     │   │
│  └────────────┘  └─────────────────┘   │
└──────────────────────────────────────────┘
         │                    │
         ▼                    ▼
┌───────────────┐    ┌───────────────┐
│    MariaDB    │    │   InfluxDB    │
│ (Relacional)  │    │ (Time Series) │
│  Puerto 3306  │    │  Puerto 8086  │
└───────────────┘    └───────────────┘
         │
         ▼
┌──────────────────────────────────────────┐
│              PHPMyAdmin                  │
│              Puerto 8080                 │
└──────────────────────────────────────────┘
```

## 🚀 Despliegue Rápido

### Requisitos Previos

- Docker y Docker Compose instalados
- Dominio configurado (DuckDNS recomendado)
- **Puertos necesarios** (recomendados para VPS con IP pública):
  - `80` (HTTP) y `443` (HTTPS)
  - `1883` (MQTT) y `8883` (MQTTS con SSL)
  - `3306` (MariaDB), `8080` (PHPMyAdmin), `8086` (InfluxDB), `8006` (Flask)

> **💡 Nota**: Si tu VPS tiene restricciones de red, puedes usar puertos alternativos. 
> Ver [DEPLOY.md](DEPLOY.md) para configuración detallada de puertos personalizados.

### Pasos de Instalación

#### 1. Clonar el repositorio

```bash
git clone https://github.com/tuusuario/enertrack.git
cd enertrack
```

#### 2. Configurar variables de entorno

```bash
cp .env.example .env
nano .env
```

Configura las siguientes variables críticas:

```bash
# MariaDB
MARIADB_ROOT_PASSWORD=tu_password_seguro
MYSQL_USER=medidor_user
MYSQL_PASSWORD=tu_mysql_password
MYSQL_DB=medidoresEnergia

# InfluxDB (generado al primer inicio)
INFLUX_URL=http://influxdb:8086
INFLUX_TOKEN=tu_token_de_influx
INFLUX_ORG=IoT
INFLUX_BUCKET=medidoresEnergia

# MQTT
DOMINIO=tu_dominio.duckdns.org
MQTT_USR=tu_usuario_mqtt
MQTT_PASS=tu_password_mqtt
PUERTO=443              # Puerto HTTPS (usa 443 si tienes IP pública)
PUERTO_MQTTS=8883       # Puerto MQTT con SSL (8883 es el estándar)

# Flask
FLASK_SECRET_KEY=$(python3 -c "import secrets; print(secrets.token_urlsafe(32))")
FERNET_KEY=$(python3 -c "from cryptography.fernet import Fernet; print(Fernet.generate_key().decode())")

# Telegram Bot
enertrackBotToken=tu_bot_token_de_telegram
```

#### 3. Crear la red Docker

```bash
docker network create docker_iot-1_default
```

#### 4. Levantar los servicios

```bash
docker compose up -d
```

#### 5. Configurar InfluxDB (Primera vez)

Accede a http://tu_servidor:8086 y:

1. Crea una organización: `IoT`
2. Crea un bucket: `medidoresEnergia`
3. Genera un token de API
4. Actualiza `INFLUX_TOKEN` en `.env`
5. Reinicia: `docker compose restart enertrack`

#### 6. Inicializar la base de datos

La base de datos se crea automáticamente. Las tablas se crean en el primer inicio.

#### 7. Acceder a la aplicación

- **EnerTrack**: http://tu_servidor:8006
- **PHPMyAdmin**: http://tu_servidor:8080
- **InfluxDB**: http://tu_servidor:8086

## 🔐 Configuración SSL

El contenedor `swag` gestiona automáticamente los certificados SSL de Let's Encrypt usando DuckDNS.

### Configurar DuckDNS

1. Crea una cuenta en https://www.duckdns.org
2. Obtén tu token de DuckDNS
3. Actualiza `/mosquitto/config/duckdns.ini`:

```ini
dns_duckdns_token=tu_token_duckdns
```

4. Los certificados se renovarán automáticamente

## 📱 Configurar Bot de Telegram

1. Habla con [@BotFather](https://t.me/botfather) en Telegram
2. Crea un bot: `/newbot`
3. Copia el token y actualiza `enertrackBotToken` en `.env`
4. Reinicia: `docker compose restart enertrack`
5. Vincula tu cuenta desde la web: Perfil → Vincular Telegram

## 🔧 Comandos Útiles

### Ver logs
```bash
docker compose logs -f enertrack
docker compose logs -f mosquitto
docker compose logs -f influxdb
```

### Reiniciar servicios
```bash
docker compose restart enertrack
docker compose restart mosquitto
docker compose restart mariadb
```

### Backup de bases de datos

#### MariaDB
```bash
docker exec mariadb mariadb-dump -u root -p medidoresEnergia > backup_mariadb.sql
```

#### InfluxDB
```bash
docker exec influxdb influx backup /tmp/backup -t tu_token
docker cp influxdb:/tmp/backup ./backup_influx/
```

### Restaurar desde backup

#### MariaDB
```bash
docker exec -i mariadb mariadb -u root -p medidoresEnergia < backup_mariadb.sql
```

#### InfluxDB
```bash
docker cp ./backup_influx/ influxdb:/tmp/backup
docker exec influxdb influx restore /tmp/backup -t tu_token
```

### Detener todo
```bash
docker compose down
```

### Eliminar todo (incluye volúmenes)
```bash
docker compose down -v
```

## 📊 Estructura del Proyecto

```
enertrack/
├── compose.yaml              # Configuración Docker Compose
├── .env                      # Variables de entorno (NO subir a Git)
├── .env.example             # Plantilla de variables
├── schema.sql               # Esquema de base de datos
├── README.md                # Este archivo
│
├── enertrack/               # Aplicación Flask
│   ├── app.py              # Lógica principal + Worker MQTT
│   ├── telegram_bot.py     # Bot de Telegram integrado
│   ├── Dockerfile          # Build de la app
│   ├── requirements.txt    # Dependencias Python
│   ├── templates/          # Vistas HTML
│   └── static/             # JS, CSS, imágenes
│
├── influxdb/               # Datos de InfluxDB (ignorado en Git)
│   ├── data/              # Base de datos de series temporales
│   └── config/            # Configuración
│
├── mariadb/               # Datos de MariaDB (ignorado en Git)
│
└── mosquitto/             # Configuración MQTT
    ├── config/            # mosquitto.conf, passwd, etc.
    ├── data/              # Datos persistentes (ignorado)
    └── log/               # Logs (ignorado)
```

## 🔒 Seguridad

- ✅ Contraseñas hasheadas con scrypt
- ✅ Consultas SQL parametrizadas
- ✅ Conexiones MQTT sobre TLS
- ✅ Tokens JWT para sesiones
- ✅ Variables de entorno para secretos
- ✅ SSL/TLS con Let's Encrypt

## 🐛 Solución de Problemas

### Los datos MQTT no llegan

```bash
# Verificar worker MQTT
docker logs enertrack | grep "MQTT\|InfluxDB"

# Verificar mosquitto
docker logs mosquitto

# Verificar que el nodo esté publicando
docker logs enertrack | grep "Dato guardado"
```

### InfluxDB no responde

```bash
# Reiniciar InfluxDB
docker compose restart influxdb

# Verificar logs
docker logs influxdb

# Verificar token
docker exec enertrack env | grep INFLUX
```

### Error de conexión a MariaDB

```bash
# Verificar que MariaDB esté corriendo
docker ps | grep mariadb

# Verificar credenciales
docker exec mariadb mariadb -u medidor_user -p

# Recrear usuario
docker exec mariadb mariadb -u root -p -e "CREATE USER IF NOT EXISTS 'medidor_user'@'%' IDENTIFIED BY 'tu_password'; GRANT ALL PRIVILEGES ON medidoresEnergia.* TO 'medidor_user'@'%'; FLUSH PRIVILEGES;"
```

## � Configuración de Puertos

### Puertos Estándar (Recomendado para VPS con IP Pública)

```bash
# En .env
PUERTO=443              # HTTPS estándar
PUERTO_MQTTS=8883       # MQTT con SSL estándar
```

```yaml
# En compose.yaml - Cambiar de:
ports:
  - ${PUERTO}:443/tcp
  - ${PUERTO_MQTTS}:8883

# A puertos fijos:
ports:
  - 443:443/tcp
  - 8883:8883
```

### Puertos Personalizados (Para VPS con Restricciones)

Si tu VPS tiene firewall restrictivo o NAT complejo, puedes usar puertos alternativos:

```bash
# En .env
PUERTO=23405            # Puerto HTTPS alternativo
PUERTO_MQTTS=23805      # Puerto MQTTS alternativo
```

Mantén las variables en `compose.yaml` como:
```yaml
ports:
  - ${PUERTO}:443/tcp
  - ${PUERTO_MQTTS}:8883
```

### Tabla de Puertos por Servicio

| Servicio | Puerto Interno | Puerto Externo Recomendado | Propósito |
|----------|---------------|---------------------------|-----------|
| SWAG (HTTP) | 80 | 80 | Redirección HTTP → HTTPS |
| SWAG (HTTPS) | 443 | 443 (o personalizado) | Aplicación web principal |
| Mosquitto (MQTT) | 1883 | 1883 | MQTT sin SSL (solo local) |
| Mosquitto (MQTTS) | 8883 | 8883 (o personalizado) | MQTT con SSL para ESP32 |
| MariaDB | 3306 | 3306 | Base de datos MySQL |
| PHPMyAdmin | 80 | 8080 | Administración de BD |
| InfluxDB | 8086 | 8086 | Base de datos de series temporales |
| EnerTrack | 8006 | 8006 | Aplicación Flask |

> **💡 Consejo de Seguridad**: En producción, considera exponer solo los puertos 80, 443 y 8883 externamente. 
> Los demás servicios pueden quedar en la red interna de Docker y accederse mediante proxy inverso.

## �📝 Migración a Otra VPS

1. **Hacer backup de datos importantes**:
   ```bash
   # Backup MariaDB
   docker exec mariadb mariadb-dump -u root -p medidoresEnergia > backup.sql
   
   # Backup InfluxDB
   tar -czf influxdb_backup.tar.gz influxdb/
   ```

2. **En la nueva VPS**:
   ```bash
   git clone https://github.com/tuusuario/enertrack.git
   cd enertrack
   cp .env.example .env
   # Configurar .env con los mismos valores
   ```

3. **Restaurar datos**:
   ```bash
   # Subir archivos de backup
   # Restaurar MariaDB
   docker compose up -d mariadb
   docker exec -i mariadb mariadb -u root -p medidoresEnergia < backup.sql
   
   # Restaurar InfluxDB
   tar -xzf influxdb_backup.tar.gz
   ```

4. **Levantar servicios**:
   ```bash
   docker network create docker_iot-1_default
   docker compose up -d
   ```

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue o pull request.

## 📄 Licencia

[Especifica tu licencia aquí]

## 👤 Autor

Ignacio Behler - [GitHub](https://github.com/ignaciobehler)

---

**¿Problemas?** Abre un issue en GitHub o contacta al mantenedor.
