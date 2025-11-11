# EnerTrack# ⚡ EnerTrack# 🔋 ENERTRACK - Plataforma de Monitoreo Energético



Sistema IoT de Monitoreo Energético en Tiempo Real con ESP32, MQTT, InfluxDB y alertas por Telegram.



## Descripción<div align="center">Plataforma web completa para monitorear y analizar el consumo eléctrico en tiempo real mediante medidores inteligentes basados en ESP32.



EnerTrack permite monitorear el consumo eléctrico de múltiples dispositivos en tiempo real, visualizar datos históricos, configurar alertas personalizadas y analizar patrones de consumo desde una interfaz web moderna.



## Características Principales![EnerTrack Logo](https://img.shields.io/badge/EnerTrack-IoT%20Energy%20Monitor-blue?style=for-the-badge)## 📋 Características



- Dashboard web interactivo con visualización en tiempo real

- Gráficos históricos por hora, día, mes y año

- Alertas por Telegram cuando se superan umbrales de consumo**Sistema IoT de Monitoreo Energético con ESP32, MQTT, InfluxDB y Alertas por Telegram**- ✅ Gestión de usuarios y nodos ESP32

- Soporte para múltiples nodos ESP32 simultáneos

- Comunicación MQTT segura con SSL/TLS- ✅ Monitoreo en tiempo real vía MQTT/MQTTS

- Gestión multiusuario con nodos compartibles

- Interfaz responsive compatible con móviles[![Docker](https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)- ✅ Dashboards interactivos con Chart.js



## Tecnologías[![Python](https://img.shields.io/badge/python-3.11-blue.svg?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)- ✅ Base de datos relacional (MariaDB) y series temporales (InfluxDB)



- **Backend**: Python 3.11 + Flask + Gunicorn[![Flask](https://img.shields.io/badge/flask-%23000.svg?style=for-the-badge&logo=flask&logoColor=white)](https://flask.palletsprojects.com/)- ✅ Alertas automáticas por Telegram

- **Frontend**: HTML5 + Bootstrap 5 + Chart.js

- **Bases de Datos**: MariaDB (relacional) + InfluxDB (series temporales)[![License](https://img.shields.io/github/license/ignaciobehler/enertrack?style=for-the-badge)](LICENSE)- ✅ Análisis de consumo por hora/día/mes/año

- **IoT**: ESP32 + MQTT (Mosquitto)

- **Proxy/SSL**: SWAG (Nginx + Let's Encrypt)- ✅ Tema claro/oscuro

- **Contenedores**: Docker + Docker Compose

[Características](#-características) •- ✅ Proxy inverso con SSL (Let's Encrypt)

## Arquitectura

[Arquitectura](#-arquitectura) •

```

ESP32 Nodos → MQTT (SSL) → Mosquitto Broker[Instalación](#-instalación-rápida) •## 🏗️ Arquitectura

                              ↓

                         InfluxDB (datos)[Documentación](#-documentación) •

                              ↓

                     Flask App ← MariaDB (usuarios)[Contribuir](#-contribuir)```

                         ↓         ↓

                    Dashboard   Telegram Bot┌─────────────┐

                         ↓

                    SWAG (SSL)</div>│   ESP32     │──MQTT──┐

                         ↓

                      Internet│  Medidores  │        │

```

---└─────────────┘        │

## Instalación Rápida

                       ▼

### Requisitos Previos

## 📖 Descripción┌──────────────────────────────────────────┐

- Docker y Docker Compose instalados

- Dominio DuckDNS (gratuito)│           Mosquitto (MQTT Broker)        │

- Bot de Telegram (@BotFather)

EnerTrack es un sistema completo de monitoreo energético en tiempo real que combina hardware IoT (ESP32) con una plataforma web moderna. Permite monitorear múltiples nodos de medición de energía, visualizar datos históricos, recibir alertas por Telegram cuando se superan umbrales configurables, y analizar patrones de consumo.│              Puerto 1883/8883            │

### Pasos de Instalación

└──────────────────────────────────────────┘

**1. Clonar el repositorio**

### 🎯 Casos de Uso                       │

```bash

git clone https://github.com/ignaciobehler/EnerTrack_V1.0.git                       ▼

cd EnerTrack_V1.0

```- 🏠 **Hogares**: Monitoreo de consumo eléctrico por habitación o electrodoméstico┌──────────────────────────────────────────┐



**2. Configurar variables de entorno**- 🏭 **Industria**: Control de consumo energético en líneas de producción│         EnerTrack (Flask App)            │



```bash- 🏢 **Edificios Comerciales**: Gestión de energía en instalaciones múltiples│              Puerto 8006                 │

cp .env.example .env

nano .env- 🌱 **Energías Renovables**: Seguimiento de generación solar/eólica│  ┌────────────┐  ┌─────────────────┐   │

```

- 📊 **Análisis de Eficiencia**: Identificación de picos de consumo y optimización│  │ Telegram   │  │  Worker MQTT    │   │

Edita las siguientes variables:

│  │    Bot     │  │  → InfluxDB     │   │

```bash

MARIADB_ROOT_PASSWORD=tu_password_seguro## ✨ Características│  └────────────┘  └─────────────────┘   │

MYSQL_PASSWORD=tu_mysql_password

INFLUX_TOKEN=tu_token_influxdb└──────────────────────────────────────────┘

DOMINIO=tu_subdominio.duckdns.org

enertrackBotToken=tu_token_bot_telegram### 🖥️ **Dashboard Web Interactivo**         │                    │

```

- 📊 Visualización en tiempo real de magnitudes eléctricas (tensión, corriente, potencia, factor de potencia, frecuencia)         ▼                    ▼

**3. Generar claves secretas**

- 📈 Gráficos históricos con diferentes períodos (hora, día, mes, año)┌───────────────┐    ┌───────────────┐

```bash

python3 generate_keys.py- 🎨 Interface moderna y responsiva con Bootstrap 5│    MariaDB    │    │   InfluxDB    │

```

- 🌓 Indicadores de estado en tiempo real (activo/desconectado/sin datos)│ (Relacional)  │    │ (Time Series) │

Copia las claves generadas en tu archivo `.env`.

- 📱 Compatible con dispositivos móviles│  Puerto 3306  │    │  Puerto 8086  │

**4. Configurar DuckDNS**

└───────────────┘    └───────────────┘

Edita `mosquitto/config/duckdns.ini`:

### 🔔 **Sistema de Alertas**         │

```ini

dns_duckdns_token=tu_token_duckdns- 📲 Notificaciones por Telegram cuando se superan umbrales de consumo         ▼

```

- ⚙️ Configuración personalizada de umbrales por nodo┌──────────────────────────────────────────┐

**5. Inicializar base de datos**

- 🔄 Sistema de histéresis para evitar spam de alertas│              PHPMyAdmin                  │

```bash

docker network create docker_iot-1_default- ⏰ Verificación cada 5 minutos con ventana de 15 minutos│              Puerto 8080                 │

docker compose up -d mariadb

sleep 10└──────────────────────────────────────────┘

docker exec -i mariadb mariadb -u root -p${MARIADB_ROOT_PASSWORD} < schema.sql

```### 📡 **Conectividad IoT**```



**6. Iniciar todos los servicios**- 🔒 MQTT con SSL/TLS (MQTTS) para comunicación segura



```bash- 🌐 Certificados automáticos con Let's Encrypt vía DuckDNS## 🚀 Despliegue Rápido

docker compose up -d

```- 📶 Soporte para múltiples nodos ESP32 simultáneos



**7. Verificar estado**- 🔌 Protocolo MQTT ligero y eficiente### Requisitos Previos



```bash

docker compose ps

docker compose logs -f enertrack### 💾 **Almacenamiento Robusto**- Docker y Docker Compose instalados

```

- ⏱️ InfluxDB para series temporales (datos de sensores)- Dominio configurado (DuckDNS recomendado)

**8. Acceder a la aplicación**

- 🗄️ MariaDB para datos de usuarios y configuración- **Puertos necesarios** (recomendados para VPS con IP pública):

Abre tu navegador en: `https://tu_dominio.duckdns.org`

- 📦 Retención configurable de datos históricos  - `80` (HTTP) y `443` (HTTPS)

## Configuración de InfluxDB

- 🔍 Consultas optimizadas para gráficos en tiempo real  - `1883` (MQTT) y `8883` (MQTTS con SSL)

1. Accede a `http://localhost:8086`

2. Crea una organización: `IoT`  - `3306` (MariaDB), `8080` (PHPMyAdmin), `8086` (InfluxDB), `8006` (Flask)

3. Crea un bucket: `medidoresEnergia`

4. Genera un token de API### 🔐 **Seguridad**

5. Copia el token a `.env` como `INFLUX_TOKEN`

- 🔑 Autenticación de usuarios con hash de contraseñas (Scrypt)> **💡 Nota**: Si tu VPS tiene restricciones de red, puedes usar puertos alternativos. 

## Configuración del Bot de Telegram

- 🛡️ Variables de entorno para secretos> Ver [DEPLOY.md](DEPLOY.md) para configuración detallada de puertos personalizados.

1. Habla con @BotFather en Telegram

2. Crea un nuevo bot: `/newbot`- 🔒 Comunicación HTTPS/TLS en todos los servicios

3. Copia el token a `.env` como `enertrackBotToken`

4. Configura comandos: `/setcommands`- 👥 Gestión multiusuario con nodos compartibles### Pasos de Instalación

   - `help - Ayuda y descripción del bot`



## Configuración de ESP32

## 🏗️ Arquitectura#### 1. Clonar el repositorio

Ejemplo de código para Arduino:



```cpp

const char* mqtt_server = "tu_dominio.duckdns.org";``````bash

const int mqtt_port = 8883;  // MQTTS con SSL

const char* mqtt_user = "enertrack_mqtt";┌─────────────────────────────────────────────────────────────────┐git clone https://github.com/tuusuario/enertrack.git

const char* mqtt_password = "tu_password_mqtt";

│                          INTERNET                               │cd enertrack

// Topics para publicar mediciones

// enertrack/{ESP_ID}/tension└─────────────────┬───────────────────────────┬───────────────────┘```

// enertrack/{ESP_ID}/corriente

// enertrack/{ESP_ID}/consumo                  │                           │

// enertrack/{ESP_ID}/fp

// enertrack/{ESP_ID}/frecuencia         ┌────────▼────────┐         ┌────────▼────────┐#### 2. Configurar variables de entorno

```

         │   DuckDNS DNS   │         │  Telegram API   │

## Uso

         └────────┬────────┘         └────────▲────────┘```bash

### Registro y Login

                  │                           │cp .env.example .env

1. Accede a la aplicación web

2. Crea una cuenta nueva         ┌────────▼──────────────────────────┴────────┐nano .env

3. Inicia sesión

         │            SWAG (Nginx + SSL)              │```

### Agregar Nodos

         │        Let's Encrypt + Reverse Proxy       │

1. Ve a "Mis Nodos"

2. Click en "Agregar Nodo"         └────────┬───────────────────────────────────┘Configura las siguientes variables críticas:

3. Ingresa el ESP_ID de tu dispositivo

4. Asigna descripción y ubicación                  │



### Configurar Alertas    ┌─────────────┼─────────────────────────┐```bash



1. Ve a "Mis Nodos"    │             │                         │# MariaDB

2. Click en "Configurar Umbral"

3. Establece el límite de potencia en kW┌───▼────┐ ┌──────▼──────┐ ┌───────▼───────────┐MARIADB_ROOT_PASSWORD=tu_password_seguro

4. Vincula tu cuenta de Telegram

5. Recibirás alertas cuando se supere el umbral│ ESP32  │ │  EnerTrack  │ │  PHPMyAdmin       │MYSQL_USER=medidor_user



## Estructura del Proyecto│ Nodos  │ │  Flask App  │ │                   │MYSQL_PASSWORD=tu_mysql_password



```│        │ │             │ │                   │MYSQL_DB=medidoresEnergia

enertrack/

├── enertrack/           # Aplicación Flask│ MQTT   │ │  Dashboards │ │  DB Management    │

│   ├── app.py          # Backend principal

│   ├── telegram_bot.py # Bot de Telegram│ Pub    │ │  API REST   │ │                   │# InfluxDB (generado al primer inicio)

│   ├── templates/      # Plantillas HTML

│   └── static/         # CSS, JS, imágenes└───┬────┘ │  Telegram   │ └─────────┬─────────┘INFLUX_URL=http://influxdb:8086

├── docs/               # Documentación

├── mosquitto/config/   # Configuración MQTT    │      │  Bot        │           │INFLUX_TOKEN=tu_token_de_influx

├── schema.sql         # Schema de base de datos

├── compose.yaml       # Docker Compose    │      └──────┬──────┘           │INFLUX_ORG=IoT

├── .env.example       # Plantilla de configuración

└── README.md          # Este archivo    │             │                  │INFLUX_BUCKET=medidoresEnergia

```

    │    ┌────────┼──────────────────┼──────────┐

## Comandos Útiles

    │    │        │                  │          │# MQTT

```bash

# Ver logs en tiempo real┌───▼────▼───┐ ┌──▼──────┐ ┌────────▼────┐ ┌───▼──────┐DOMINIO=tu_dominio.duckdns.org

docker compose logs -f

│  Mosquitto │ │ InfluxDB│ │  MariaDB    │ │ MariaDB  │MQTT_USR=tu_usuario_mqtt

# Reiniciar un servicio

docker compose restart enertrack│  MQTT      │ │ Series  │ │  Users/     │ │          │MQTT_PASS=tu_password_mqtt



# Reconstruir después de cambios│  Broker    │ │ Time DB │ │  Nodes      │ │          │PUERTO=443              # Puerto HTTPS (usa 443 si tienes IP pública)

docker compose build enertrack

docker compose up -d enertrack└────────────┘ └─────────┘ └─────────────┘ └──────────┘PUERTO_MQTTS=8883       # Puerto MQTT con SSL (8883 es el estándar)



# Detener todo```

docker compose down

```# Flask



## Documentación### 🐳 Servicios DockerFLASK_SECRET_KEY=$(python3 -c "import secrets; print(secrets.token_urlsafe(32))")



- [DEPLOY.md](docs/DEPLOY.md) - Guía completa de despliegueFERNET_KEY=$(python3 -c "from cryptography.fernet import Fernet; print(Fernet.generate_key().decode())")

- [CONTRIBUTING.md](docs/CONTRIBUTING.md) - Cómo contribuir al proyecto

| Servicio | Tecnología | Puerto | Descripción |

## Seguridad

|----------|------------|--------|-------------|# Telegram Bot

- Autenticación de usuarios con hash de contraseñas (Scrypt)

- Variables de entorno para secretos| **enertrack** | Python 3.11 + Flask + Gunicorn | 8006 | Aplicación web y bot de Telegram |enertrackBotToken=tu_bot_token_de_telegram

- Comunicación HTTPS/TLS en todos los servicios

- MQTT con SSL/TLS (MQTTS)| **mariadb** | MariaDB | 3306 | Base de datos relacional |```

- Archivo `.env` excluido del repositorio

| **influxdb** | InfluxDB 2.x | 8086 | Base de datos de series temporales |

## Contribuir

| **mosquitto** | Eclipse Mosquitto | 1883, 8883 | Broker MQTT con SSL |#### 3. Crear la red Docker

Las contribuciones son bienvenidas. Por favor:

| **swag** | LinuxServer SWAG | 80, 443 | Nginx reverse proxy + Let's Encrypt |

1. Fork el proyecto

2. Crea una rama: `git checkout -b feature/nueva-funcionalidad`| **phpmyadmin** | PHPMyAdmin | 8080 | Administración de BD web |```bash

3. Commit tus cambios: `git commit -m 'Add: nueva funcionalidad'`

4. Push: `git push origin feature/nueva-funcionalidad`docker network create docker_iot-1_default

5. Abre un Pull Request

## 🚀 Instalación Rápida```

## Licencia



Este proyecto está bajo la Licencia MIT. Ver [LICENSE](LICENSE) para más detalles.

### Prerrequisitos#### 4. Levantar los servicios

## Autores



- Ignacio Behler - [@ignaciobehler](https://github.com/ignaciobehler)

- Emiliano Lukoski- Docker y Docker Compose instalados```bash



## Soporte- Dominio DuckDNS configurado (gratuito)docker compose up -d



- Issues: [GitHub Issues](https://github.com/ignaciobehler/EnerTrack_V1.0/issues)- Bot de Telegram creado con @BotFather```

- Documentación completa en el directorio `/docs`



---

### 1️⃣ Clonar el Repositorio#### 5. Configurar InfluxDB (Primera vez)

Desarrollado con ❤️ para la comunidad IoT



```bashAccede a http://tu_servidor:8086 y:

git clone https://github.com/ignaciobehler/enertrack.git

cd enertrack1. Crea una organización: `IoT`

```2. Crea un bucket: `medidoresEnergia`

3. Genera un token de API

### 2️⃣ Configurar Variables de Entorno4. Actualiza `INFLUX_TOKEN` en `.env`

5. Reinicia: `docker compose restart enertrack`

```bash

# Copiar plantilla#### 6. Inicializar la base de datos

cp .env.example .env

La base de datos se crea automáticamente. Las tablas se crean en el primer inicio.

# Editar con tus valores

nano .env#### 7. Acceder a la aplicación

```

- **EnerTrack**: http://tu_servidor:8006

**Variables críticas a configurar:**- **PHPMyAdmin**: http://tu_servidor:8080

- **InfluxDB**: http://tu_servidor:8086

```bash

# Base de datos## 🔐 Configuración SSL

MARIADB_ROOT_PASSWORD=tu_password_seguro

MYSQL_PASSWORD=tu_mysql_passwordEl contenedor `swag` gestiona automáticamente los certificados SSL de Let's Encrypt usando DuckDNS.



# InfluxDB (genera el token en el paso 3)### Configurar DuckDNS

INFLUX_TOKEN=tu_token_influxdb

1. Crea una cuenta en https://www.duckdns.org

# Dominio2. Obtén tu token de DuckDNS

DOMINIO=tu_subdominio.duckdns.org3. Actualiza `/mosquitto/config/duckdns.ini`:



# Telegram```ini

enertrackBotToken=tu_token_bot_telegramdns_duckdns_token=tu_token_duckdns

```

# Claves secretas (generar con generate_keys.py)

FLASK_SECRET_KEY=tu_clave_secreta4. Los certificados se renovarán automáticamente

FERNET_KEY=tu_clave_fernet

```## 📱 Configurar Bot de Telegram



### 3️⃣ Generar Claves Secretas1. Habla con [@BotFather](https://t.me/botfather) en Telegram

2. Crea un bot: `/newbot`

```bash3. Copia el token y actualiza `enertrackBotToken` en `.env`

python3 generate_keys.py4. Reinicia: `docker compose restart enertrack`

```5. Vincula tu cuenta desde la web: Perfil → Vincular Telegram



Copia las claves generadas en tu archivo `.env`.## 🔧 Comandos Útiles



### 4️⃣ Configurar DuckDNS### Ver logs

```bash

Edita `mosquitto/config/duckdns.ini`:docker compose logs -f enertrack

docker compose logs -f mosquitto

```inidocker compose logs -f influxdb

dns_duckdns_token=tu_token_duckdns```

```

### Reiniciar servicios

### 5️⃣ Inicializar Base de Datos```bash

docker compose restart enertrack

```bashdocker compose restart mosquitto

# Crear red Dockerdocker compose restart mariadb

docker network create docker_iot-1_default```



# Iniciar MariaDB### Backup de bases de datos

docker compose up -d mariadb

#### MariaDB

# Esperar 10 segundos```bash

sleep 10docker exec mariadb mariadb-dump -u root -p medidoresEnergia > backup_mariadb.sql

```

# Importar schema

docker exec -i mariadb mariadb -u root -p${MARIADB_ROOT_PASSWORD} < schema.sql#### InfluxDB

``````bash

docker exec influxdb influx backup /tmp/backup -t tu_token

### 6️⃣ Iniciar Todos los Serviciosdocker cp influxdb:/tmp/backup ./backup_influx/

```

```bash

docker compose up -d### Restaurar desde backup

```

#### MariaDB

### 7️⃣ Verificar Estado```bash

docker exec -i mariadb mariadb -u root -p medidoresEnergia < backup_mariadb.sql

```bash```

docker compose ps

docker compose logs -f enertrack#### InfluxDB

``````bash

docker cp ./backup_influx/ influxdb:/tmp/backup

### 8️⃣ Acceder a la Aplicacióndocker exec influxdb influx restore /tmp/backup -t tu_token

```

- **Web**: `https://tu_dominio.duckdns.org`

- **PHPMyAdmin**: `https://tu_dominio.duckdns.org/phpmyadmin`### Detener todo

```bash

## 📚 Documentacióndocker compose down

```

### 📖 Guías Detalladas

### Eliminar todo (incluye volúmenes)

- **[DEPLOY.md](docs/DEPLOY.md)** - Guía completa de despliegue paso a paso```bash

- **[CONTRIBUTING.md](docs/CONTRIBUTING.md)** - Cómo contribuir al proyectodocker compose down -v

- **[CHECKLIST_GITHUB.md](docs/CHECKLIST_GITHUB.md)** - Checklist antes de subir a GitHub```

- **[SECURITY_ANALYSIS.md](SECURITY_ANALYSIS.md)** - Análisis de seguridad del proyecto

## 📊 Estructura del Proyecto

### ⚙️ Configuración de Servicios

```

#### InfluxDBenertrack/

├── compose.yaml              # Configuración Docker Compose

```bash├── .env                      # Variables de entorno (NO subir a Git)

# Acceder a la interfaz web├── .env.example             # Plantilla de variables

http://localhost:8086├── schema.sql               # Esquema de base de datos

├── README.md                # Este archivo

# Crear organización: IoT│

# Crear bucket: medidoresEnergia├── enertrack/               # Aplicación Flask

# Generar token de API│   ├── app.py              # Lógica principal + Worker MQTT

# Copiar token a .env como INFLUX_TOKEN│   ├── telegram_bot.py     # Bot de Telegram integrado

```│   ├── Dockerfile          # Build de la app

│   ├── requirements.txt    # Dependencias Python

#### Bot de Telegram│   ├── templates/          # Vistas HTML

│   └── static/             # JS, CSS, imágenes

```bash│

# 1. Hablar con @BotFather en Telegram├── influxdb/               # Datos de InfluxDB (ignorado en Git)

# 2. Crear nuevo bot: /newbot│   ├── data/              # Base de datos de series temporales

# 3. Copiar token a .env como enertrackBotToken│   └── config/            # Configuración

# 4. Configurar comandos del bot: /setcommands│

#    help - Ayuda y descripción del bot├── mariadb/               # Datos de MariaDB (ignorado en Git)

```│

└── mosquitto/             # Configuración MQTT

#### ESP32 (Arduino)    ├── config/            # mosquitto.conf, passwd, etc.

    ├── data/              # Datos persistentes (ignorado)

Configurar en el código del ESP32:    └── log/               # Logs (ignorado)

```

```cpp

const char* mqtt_server = "tu_dominio.duckdns.org";## 🔒 Seguridad

const int mqtt_port = 8883;  // MQTTS con SSL

const char* mqtt_user = "enertrack_mqtt";- ✅ Contraseñas hasheadas con scrypt

const char* mqtt_password = "tu_password_mqtt";- ✅ Consultas SQL parametrizadas

- ✅ Conexiones MQTT sobre TLS

// Topics de publicación- ✅ Tokens JWT para sesiones

// enertrack/{ESP_ID}/tension- ✅ Variables de entorno para secretos

// enertrack/{ESP_ID}/corriente- ✅ SSL/TLS con Let's Encrypt

// enertrack/{ESP_ID}/consumo

// enertrack/{ESP_ID}/fp## 🐛 Solución de Problemas

// enertrack/{ESP_ID}/frecuencia

```### Los datos MQTT no llegan



### 🔧 Scripts Útiles```bash

# Verificar worker MQTT

```bashdocker logs enertrack | grep "MQTT\|InfluxDB"

# Ver logs en tiempo real

docker compose logs -f# Verificar mosquitto

docker logs mosquitto

# Reiniciar un servicio

docker compose restart enertrack# Verificar que el nodo esté publicando

docker logs enertrack | grep "Dato guardado"

# Rebuild después de cambios```

docker compose build enertrack

docker compose up -d enertrack### InfluxDB no responde



# Backup de bases de datos```bash

./backup.sh  # (crear script personalizado)# Reiniciar InfluxDB

docker compose restart influxdb

# Detener todo

docker compose down# Verificar logs

```docker logs influxdb



## 📊 Uso# Verificar token

docker exec enertrack env | grep INFLUX

### Registro y Login```



1. Accede a `https://tu_dominio.duckdns.org`### Error de conexión a MariaDB

2. Crea una cuenta nueva

3. Inicia sesión```bash

# Verificar que MariaDB esté corriendo

### Agregar Nodosdocker ps | grep mariadb



1. Ve a "Mis Nodos"# Verificar credenciales

2. Click en "Agregar Nodo"docker exec mariadb mariadb -u medidor_user -p

3. Ingresa el ESP_ID de tu dispositivo

4. Asigna descripción y ubicación# Recrear usuario

docker exec mariadb mariadb -u root -p -e "CREATE USER IF NOT EXISTS 'medidor_user'@'%' IDENTIFIED BY 'tu_password'; GRANT ALL PRIVILEGES ON medidoresEnergia.* TO 'medidor_user'@'%'; FLUSH PRIVILEGES;"

### Configurar Alertas```



1. Ve a "Mis Nodos"## � Configuración de Puertos

2. Click en "Configurar Umbral" en un nodo

3. Establece el límite de potencia en kW### Puertos Estándar (Recomendado para VPS con IP Pública)

4. Vincula tu cuenta de Telegram

5. Recibirás alertas cuando se supere el umbral```bash

# En .env

### Visualizar DatosPUERTO=443              # HTTPS estándar

PUERTO_MQTTS=8883       # MQTT con SSL estándar

- **Dashboard General**: Vista de todos tus nodos```

- **Dashboard Individual**: Click en un nodo para ver detalles

- **Consumo Global**: Análisis comparativo de todos los nodos```yaml

- **Gráficos por Magnitud**: Click en una magnitud para ver histórico detallado# En compose.yaml - Cambiar de:

ports:

## 🛠️ Desarrollo  - ${PUERTO}:443/tcp

  - ${PUERTO_MQTTS}:8883

### Estructura del Proyecto

# A puertos fijos:

```ports:

enertrack/  - 443:443/tcp

├── enertrack/              # Aplicación Flask  - 8883:8883

│   ├── app.py             # Backend principal```

│   ├── telegram_bot.py    # Bot de Telegram

│   ├── templates/         # Templates HTML### Puertos Personalizados (Para VPS con Restricciones)

│   ├── static/            # CSS, JS, imágenes

│   ├── Dockerfile         # Imagen DockerSi tu VPS tiene firewall restrictivo o NAT complejo, puedes usar puertos alternativos:

│   └── requirements.txt   # Dependencias Python

├── docs/                  # Documentación```bash

├── mosquitto/             # Configuración MQTT# En .env

│   └── config/PUERTO=23405            # Puerto HTTPS alternativo

├── swag/                  # Configuración NginxPUERTO_MQTTS=23805      # Puerto MQTTS alternativo

│   └── nginx/```

├── schema.sql            # Schema de base de datos

├── compose.yaml          # Docker ComposeMantén las variables en `compose.yaml` como:

├── .env.example          # Plantilla de variables```yaml

├── generate_keys.py      # Generador de clavesports:

└── README.md             # Este archivo  - ${PUERTO}:443/tcp

```  - ${PUERTO_MQTTS}:8883

```

### Variables de Entorno

### Tabla de Puertos por Servicio

Ver [`.env.example`](.env.example) para la lista completa de variables configurables.

| Servicio | Puerto Interno | Puerto Externo Recomendado | Propósito |

### Base de Datos|----------|---------------|---------------------------|-----------|

| SWAG (HTTP) | 80 | 80 | Redirección HTTP → HTTPS |

**MariaDB (Relacional)**:| SWAG (HTTPS) | 443 | 443 (o personalizado) | Aplicación web principal |

- `Usuarios` - Información de usuarios| Mosquitto (MQTT) | 1883 | 1883 | MQTT sin SSL (solo local) |

- `Nodos` - Dispositivos ESP32 registrados| Mosquitto (MQTTS) | 8883 | 8883 (o personalizado) | MQTT con SSL para ESP32 |

- `UsuariosNodos` - Relación usuario-nodo con permisos| MariaDB | 3306 | 3306 | Base de datos MySQL |

- `UmbralesNodo` - Configuración de alertas por nodo| PHPMyAdmin | 80 | 8080 | Administración de BD |

| InfluxDB | 8086 | 8086 | Base de datos de series temporales |

**InfluxDB (Series Temporales)**:| EnerTrack | 8006 | 8006 | Aplicación Flask |

- Measurement: `tension`, `corriente`, `consumo`, `fp`, `frecuencia`

- Tag: `esp_id` (identificador del nodo)> **💡 Consejo de Seguridad**: En producción, considera exponer solo los puertos 80, 443 y 8883 externamente. 

- Field: `valor` (medición numérica)> Los demás servicios pueden quedar en la red interna de Docker y accederse mediante proxy inverso.



## 🤝 Contribuir## �📝 Migración a Otra VPS



¡Las contribuciones son bienvenidas! Por favor lee [CONTRIBUTING.md](docs/CONTRIBUTING.md) para detalles sobre nuestro código de conducta y el proceso para enviar pull requests.1. **Hacer backup de datos importantes**:

   ```bash

### Pasos Rápidos   # Backup MariaDB

   docker exec mariadb mariadb-dump -u root -p medidoresEnergia > backup.sql

1. Fork el proyecto   

2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)   # Backup InfluxDB

3. Commit tus cambios (`git commit -m 'Add: nueva funcionalidad increíble'`)   tar -czf influxdb_backup.tar.gz influxdb/

4. Push a la rama (`git push origin feature/AmazingFeature`)   ```

5. Abre un Pull Request

2. **En la nueva VPS**:

## 📝 Licencia   ```bash

   git clone https://github.com/tuusuario/enertrack.git

Este proyecto está bajo la Licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.   cd enertrack

   cp .env.example .env

## 👥 Autores   # Configurar .env con los mismos valores

   ```

- **Ignacio Behler** - [@ignaciobehler](https://github.com/ignaciobehler)

- **Emiliano Lukoski**3. **Restaurar datos**:

   ```bash

## 🙏 Agradecimientos   # Subir archivos de backup

   # Restaurar MariaDB

- Comunidad de Arduino y ESP32   docker compose up -d mariadb

- Proyecto Eclipse Mosquitto   docker exec -i mariadb mariadb -u root -p medidoresEnergia < backup.sql

- InfluxData por InfluxDB   

- LinuxServer.io por las imágenes Docker   # Restaurar InfluxDB

- Todos los contribuidores   tar -xzf influxdb_backup.tar.gz

   ```

## 📞 Soporte

4. **Levantar servicios**:

- 📧 Issues: [GitHub Issues](https://github.com/ignaciobehler/enertrack/issues)   ```bash

- 📖 Wiki: [GitHub Wiki](https://github.com/ignaciobehler/enertrack/wiki)   docker network create docker_iot-1_default

- 💬 Discusiones: [GitHub Discussions](https://github.com/ignaciobehler/enertrack/discussions)   docker compose up -d

   ```

## 🗺️ Roadmap

## 🤝 Contribuciones

- [ ] Dashboard móvil nativo (React Native)

- [ ] Integración con Home AssistantLas contribuciones son bienvenidas. Por favor, abre un issue o pull request.

- [ ] Exportación de datos a CSV/Excel

- [ ] Reportes automáticos por email## 📄 Licencia

- [ ] Predicción de consumo con ML

- [ ] Soporte para más tipos de sensores[Especifica tu licencia aquí]

- [ ] API REST documentada con Swagger

- [ ] Tests automatizados## 👤 Autor



---Ignacio Behler - [GitHub](https://github.com/ignaciobehler)



<div align="center">## 📚 Documentación Adicional



**⭐ Si te gusta este proyecto, dale una estrella en GitHub ⭐**Para información adicional sobre el proyecto, consulta la carpeta [`docs/`](docs/):



Hecho con ❤️ por la comunidad IoT- **[DEPLOY.md](docs/DEPLOY.md)** - Guía detallada de despliegue en producción

- **[CONTRIBUTING.md](docs/CONTRIBUTING.md)** - Guía para contribuir al proyecto

</div>- **[CHECKLIST_GITHUB.md](docs/CHECKLIST_GITHUB.md)** - Checklist de tareas para GitHub

- **[.env.example](docs/.env.example)** - Ejemplo de archivo de variables de entorno
- **[compose.yaml.backup](docs/compose.yaml.backup)** - Backup de configuración Docker Compose

---

**¿Problemas?** Abre un issue en GitHub o contacta al mantenedor.
