# 🚀 Guía de Despliegue - EnerTrack

Esta guía te ayudará a desplegar EnerTrack en cualquier VPS desde cero.

## 📋 Requisitos del Servidor

- **Sistema Operativo**: Ubuntu 20.04+ / Debian 11+
- **RAM**: Mínimo 2GB (Recomendado 4GB)
- **CPU**: 2 cores mínimo
- **Disco**: 20GB mínimo
- **Puertos necesarios** (valores recomendados para VPS con IP pública):
  - `80` - HTTP (redirige a HTTPS)
  - `443` - HTTPS (aplicación web principal)
  - `1883` - MQTT sin encriptación (opcional, solo para testing local)
  - `8883` - MQTTS (MQTT con SSL/TLS) - **Recomendado para ESP32**
  - `3306` - MariaDB (solo si necesitas acceso externo)
  - `8080` - PHPMyAdmin (solo si necesitas acceso externo)
  - `8086` - InfluxDB (solo si necesitas acceso externo)
  - `8006` - EnerTrack Flask App (puerto interno, accesible vía proxy)

> **💡 Nota sobre puertos**: Si tu VPS tiene restricciones de red o firewalls complejos, 
> puedes usar puertos alternativos (ej: 23405 para HTTPS, 23805 para MQTTS). 
> Simplemente actualiza las variables `PUERTO` y `PUERTO_MQTTS` en el archivo `.env` 
> y ajusta los puertos en `compose.yaml` según tus necesidades.

## 🔧 Paso 1: Preparar el Servidor

### 1.1 Actualizar el sistema

```bash
sudo apt update && sudo apt upgrade -y
```

### 1.2 Instalar Docker

```bash
# Instalar dependencias
sudo apt install -y apt-transport-https ca-certificates curl software-properties-common

# Agregar repositorio de Docker
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Instalar Docker
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin

# Verificar instalación
docker --version
docker compose version
```

### 1.3 Agregar usuario al grupo docker (opcional)

```bash
sudo usermod -aG docker $USER
# Cerrar y volver a iniciar sesión para que tome efecto
```

### 1.4 Instalar Git

```bash
sudo apt install -y git
```

## 📥 Paso 2: Clonar el Repositorio

```bash
cd ~
git clone https://github.com/ignaciobehler/enertrack.git
cd enertrack
```

## ⚙️ Paso 3: Configurar Variables de Entorno

### 3.1 Copiar plantilla

```bash
cp .env.example .env
```

### 3.2 Generar claves secretas

```bash
# Opción 1: Usar el script Python (requiere cryptography)
docker run --rm python:3.11 python3 -c "
import secrets
from cryptography.fernet import Fernet
print(f'FLASK_SECRET_KEY={secrets.token_urlsafe(32)}')
print(f'FERNET_KEY={Fernet.generate_key().decode()}')
"

# Opción 2: Generar manualmente
python3 -c "import secrets; print('FLASK_SECRET_KEY=' + secrets.token_urlsafe(32))"
```

### 3.3 Editar .env

```bash
nano .env
```

Configura **como mínimo** estas variables:

```bash
# MariaDB - Cambiar passwords
MARIADB_ROOT_PASSWORD=tu_password_seguro_aqui
MYSQL_USER=medidor_user
MYSQL_PASSWORD=otro_password_seguro
MYSQL_DB=medidoresEnergia
MYSQL_HOST=mariadb
MARIADB_SERVER=mariadb

# InfluxDB - Se configurará después
INFLUX_URL=http://influxdb:8086
INFLUX_TOKEN=SE_GENERARA_DESPUES
INFLUX_ORG=IoT
INFLUX_BUCKET=medidoresEnergia

# MQTT - Tu dominio y credenciales
SERVIDOR=tu_dominio.duckdns.org
DOMINIO=tu_dominio.duckdns.org
PUERTO=443              # Puerto HTTPS estándar (o usa un puerto alternativo si tienes restricciones)
PUERTO_MQTTS=8883       # Puerto MQTT con SSL estándar (recomendado para ESP32)
MQTT_USR=tu_usuario_mqtt
MQTT_PASS=tu_password_mqtt

# Flask - Las claves generadas en 3.2
FLASK_SECRET_KEY=<clave_generada>
FERNET_KEY=<clave_generada>

# Telegram Bot - Obtener de @BotFather
enertrackBotToken=tu_token_aqui
```

> **💡 Consejo sobre puertos**: 
> - Si tu VPS tiene **IP pública sin restricciones**: Usa `PUERTO=443` y `PUERTO_MQTTS=8883` (puertos estándar)
> - Si tu VPS tiene **firewall restrictivo o NAT**: Usa puertos alternativos que tengas disponibles
> - Los ESP32 se conectan al puerto `PUERTO_MQTTS` para enviar datos con seguridad SSL/TLS

## 🌐 Paso 4: Configurar DuckDNS (SSL Certificates)

### 4.1 Crear cuenta en DuckDNS

1. Ve a https://www.duckdns.org
2. Inicia sesión con GitHub/Google
3. Crea un subdominio: `tuproyecto.duckdns.org`
4. Apunta el subdominio a la IP de tu VPS
5. Copia tu token de DuckDNS

### 4.2 Configurar token en mosquitto

```bash
nano mosquitto/config/duckdns.ini
```

Contenido:

```ini
dns_duckdns_token=TU_TOKEN_DE_DUCKDNS
```

### 4.3 Actualizar dominio en mosquitto.conf

```bash
nano mosquitto/config/mosquitto.conf
```

Busca las líneas con `YOUR_DOMAIN.duckdns.org` y reemplázalas con tu dominio real:

```properties
cafile /var/tmp/live/tu_dominio.duckdns.org/chain.pem
certfile /var/tmp/live/tu_dominio.duckdns.org/cert.pem
keyfile /var/tmp/live/tu_dominio.duckdns.org/privkey.pem
```

### 4.4 Crear archivo de passwords MQTT

```bash
docker run --rm -v $(pwd)/mosquitto/config:/config eclipse-mosquitto mosquitto_passwd -c /config/passwd tu_usuario_mqtt
```

Ingresa la contraseña cuando se te solicite.

## 🚀 Paso 5: Iniciar Servicios

### 5.0 (Opcional) Ajustar puertos en compose.yaml

Si quieres usar **puertos estándar** en lugar de los configurados por defecto, edita `compose.yaml`:

```bash
nano compose.yaml
```

**Cambios recomendados para VPS con IP pública:**

```yaml
# SWAG (Proxy SSL)
ports:
  - 443:443/tcp     # Cambiar ${PUERTO}:443 por 443:443
  - 80:80

# Mosquitto MQTT
ports:
  - 1883:1883       # MQTT sin SSL (solo para testing local)
  - 8883:8883       # Cambiar ${PUERTO_MQTTS}:8883 por 8883:8883
```

**Ejemplo de líneas a cambiar:**

```yaml
# Antes (con variables para puertos personalizados)
ports:
  - ${PUERTO}:443/tcp
  - ${PUERTO_MQTTS}:8883

# Después (puertos estándar fijos)
ports:
  - 443:443/tcp
  - 8883:8883
```

> **⚠️ Importante**: Si cambias los puertos en `compose.yaml`, asegúrate de que coincidan con los valores en `.env`

### 5.1 Crear red Docker

```bash
docker network create docker_iot-1_default
```

### 5.2 Levantar servicios

```bash
# Opción 1: Usar el script de inicialización
./init.sh

# Opción 2: Manual
docker compose up -d
```

### 5.3 Verificar que todo esté corriendo

```bash
docker compose ps
```

Deberías ver todos los servicios `Up`:
- mariadb
- phpmyadmin
- swag
- mosquitto
- clientemqtt
- influxdb
- enertrack

## 📊 Paso 6: Configurar InfluxDB (Primera vez)

### 6.1 Acceder a InfluxDB

Abre en el navegador: `http://TU_IP:8086`

### 6.2 Completar setup inicial

1. **Get Started** → Configurar:
   - Username: admin
   - Password: (elige uno seguro)
   - Organization: `IoT`
   - Bucket: `medidoresEnergia`

2. Click en **Quick Start**

3. **Generar Token de API**:
   - Click en **Load Data** → **API Tokens**
   - Click en **Generate API Token** → **All Access API Token**
   - Copia el token generado

### 6.3 Actualizar .env con el token

```bash
nano .env
```

Actualiza:
```bash
INFLUX_TOKEN=tu_token_generado_aqui
```

### 6.4 Reiniciar enertrack

```bash
docker compose restart enertrack
```

### 6.5 Verificar conexión

```bash
docker logs enertrack | grep InfluxDB
```

Deberías ver: `✅ Conectado a InfluxDB: http://influxdb:8086`

## 🤖 Paso 7: Configurar Bot de Telegram

### 7.1 Crear bot con BotFather

1. Abre Telegram y busca [@BotFather](https://t.me/botfather)
2. Envía: `/newbot`
3. Sigue las instrucciones (nombre y username)
4. Copia el token que te da

### 7.2 Actualizar .env

```bash
nano .env
```

```bash
enertrackBotToken=TU_TOKEN_DE_TELEGRAM
```

### 7.3 Reiniciar enertrack

```bash
docker compose restart enertrack
```

### 7.4 Verificar bot

```bash
docker logs enertrack | grep -i telegram
```

## 🔐 Paso 8: Configurar Certificados SSL

Los certificados se renuevan automáticamente con Let's Encrypt vía DuckDNS.

### Verificar renovación

```bash
docker logs swag | grep -i cert
```

Si ves errores, verifica:
1. Que tu dominio DuckDNS apunte a la IP correcta
2. Que el token de DuckDNS sea correcto en `mosquitto/config/duckdns.ini`
3. Que los puertos 80 y 443 estén abiertos

## ✅ Paso 9: Verificar Instalación

### 9.1 Acceder a la aplicación

Abre en el navegador:
- **Local**: `http://TU_IP:8006`
- **Con SSL**: `https://tu_dominio.duckdns.org:23405/enertrack`

### 9.2 Crear primer usuario

1. Click en **Registrarse**
2. Completa el formulario
3. Inicia sesión

### 9.3 Verificar servicios auxiliares

- **PHPMyAdmin**: `http://TU_IP:8080`
  - Servidor: mariadb
  - Usuario: medidor_user
  - Password: (el de .env)

- **InfluxDB**: `http://TU_IP:8086`

### 9.4 Verificar MQTT

```bash
docker logs enertrack | tail -30
```

Busca mensajes como:
```
✅ Suscrito a tópico MQTT global: enertrack/#
✅ Dato guardado en InfluxDB: enertrack/ESP_ID/tension=230.5
```

## 🔄 Paso 10: Configurar Backup Automático (Opcional)

### Crear script de backup

```bash
nano ~/backup_enertrack.sh
```

Contenido:

```bash
#!/bin/bash
BACKUP_DIR=~/enertrack_backups
mkdir -p $BACKUP_DIR
DATE=$(date +%Y%m%d_%H%M%S)

# Backup MariaDB
docker exec mariadb mariadb-dump -u root -p$MARIADB_ROOT_PASSWORD medidoresEnergia > $BACKUP_DIR/mariadb_$DATE.sql

# Backup InfluxDB
tar -czf $BACKUP_DIR/influxdb_$DATE.tar.gz ~/enertrack/influxdb/

# Eliminar backups antiguos (más de 7 días)
find $BACKUP_DIR -name "*.sql" -mtime +7 -delete
find $BACKUP_DIR -name "*.tar.gz" -mtime +7 -delete

echo "Backup completado: $DATE"
```

### Configurar cron

```bash
chmod +x ~/backup_enertrack.sh
crontab -e
```

Agregar:
```bash
# Backup diario a las 3 AM
0 3 * * * ~/backup_enertrack.sh >> ~/backup_enertrack.log 2>&1
```

## 🔧 Solución de Problemas

### InfluxDB no responde

```bash
docker logs influxdb
docker compose restart influxdb
```

### MariaDB error de conexión

```bash
docker exec mariadb mariadb -u root -p
# Recrear usuario si es necesario
```

### Mosquitto no acepta conexiones SSL

```bash
docker logs mosquitto
# Verificar certificados
ls -la swag/etc/letsencrypt/live/TU_DOMINIO/
```

### Worker MQTT no guarda datos

```bash
docker logs enertrack | grep "MQTT\|InfluxDB"
```

## 📱 Vinculación con Telegram

1. Inicia sesión en EnerTrack
2. Ve a **Perfil** o **Mis Nodos**
3. Click en **Vincular con Telegram**
4. Copia el enlace generado
5. Ábrelo en Telegram
6. ¡Listo! Recibirás alertas automáticas

## 🎉 ¡Despliegue Completado!

Tu instancia de EnerTrack está lista. Ahora puedes:

1. Agregar nodos ESP32
2. Configurar umbrales de alertas
3. Ver dashboards en tiempo real
4. Recibir notificaciones por Telegram

---

**¿Problemas?** Revisa los logs con `docker compose logs -f`
