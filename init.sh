#!/bin/bash
# ===================================================================
# ENERTRACK - Script de Inicialización
# ===================================================================
# Este script configura el entorno inicial para EnerTrack

set -e

echo "🔋 Inicializando EnerTrack..."
echo ""

# Colores
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Verificar Docker
if ! command -v docker &> /dev/null; then
    echo -e "${RED}❌ Docker no está instalado${NC}"
    echo "Por favor instala Docker: https://docs.docker.com/get-docker/"
    exit 1
fi

# Verificar Docker Compose
if ! command -v docker compose &> /dev/null; then
    echo -e "${RED}❌ Docker Compose no está instalado${NC}"
    echo "Por favor instala Docker Compose"
    exit 1
fi

echo -e "${GREEN}✅ Docker y Docker Compose detectados${NC}"
echo ""

# Verificar archivo .env
if [ ! -f .env ]; then
    echo -e "${YELLOW}⚠️  Archivo .env no encontrado${NC}"
    echo "Copiando .env.example a .env..."
    cp .env.example .env
    echo -e "${YELLOW}📝 Por favor edita .env con tus configuraciones:${NC}"
    echo "   nano .env"
    echo ""
    echo -e "${YELLOW}Variables críticas a configurar:${NC}"
    echo "   - MARIADB_ROOT_PASSWORD"
    echo "   - MYSQL_PASSWORD"
    echo "   - INFLUX_TOKEN"
    echo "   - DOMINIO"
    echo "   - MQTT_USR y MQTT_PASS"
    echo "   - FLASK_SECRET_KEY"
    echo "   - FERNET_KEY"
    echo "   - enertrackBotToken"
    echo ""
    read -p "Presiona ENTER cuando hayas configurado .env..."
fi

echo -e "${GREEN}✅ Archivo .env encontrado${NC}"
echo ""

# Crear red Docker si no existe
echo "🌐 Verificando red Docker..."
if ! docker network inspect docker_iot-1_default &> /dev/null; then
    echo "Creando red docker_iot-1_default..."
    docker network create docker_iot-1_default
    echo -e "${GREEN}✅ Red creada${NC}"
else
    echo -e "${GREEN}✅ Red ya existe${NC}"
fi
echo ""

# Crear carpetas necesarias
echo "📁 Creando estructura de carpetas..."
mkdir -p mariadb influxdb/data influxdb/config mosquitto/data mosquitto/log
echo -e "${GREEN}✅ Carpetas creadas${NC}"
echo ""

# Verificar archivo de configuración de mosquitto
if [ ! -f mosquitto/config/mosquitto.conf ]; then
    echo -e "${YELLOW}⚠️  Archivo mosquitto.conf no encontrado${NC}"
    echo "Creando configuración básica..."
    mkdir -p mosquitto/config
    cat > mosquitto/config/mosquitto.conf << 'EOF'
listener 1883
protocol mqtt
allow_anonymous true

listener 8883
protocol mqtt
cafile /var/tmp/live/DOMINIO/chain.pem
certfile /var/tmp/live/DOMINIO/cert.pem
keyfile /var/tmp/live/DOMINIO/privkey.pem
password_file /mosquitto/config/passwd
EOF
    echo -e "${YELLOW}⚠️  Recuerda actualizar mosquitto.conf con tu dominio${NC}"
fi
echo ""

# Levantar servicios
echo "🚀 Levantando servicios..."
echo ""
docker compose up -d

echo ""
echo -e "${GREEN}✅ Servicios iniciados correctamente${NC}"
echo ""
echo "📊 Estado de los contenedores:"
docker compose ps
echo ""

echo "🌐 Accesos:"
echo "   EnerTrack:   http://localhost:8006"
echo "   PHPMyAdmin:  http://localhost:8080"
echo "   InfluxDB:    http://localhost:8086"
echo ""

echo -e "${YELLOW}⚠️  IMPORTANTE - Configuración inicial de InfluxDB:${NC}"
echo "1. Accede a http://localhost:8086"
echo "2. Configura:"
echo "   - Organización: IoT"
echo "   - Bucket: medidoresEnergia"
echo "   - Genera un token de API"
echo "3. Actualiza INFLUX_TOKEN en .env"
echo "4. Reinicia: docker compose restart enertrack"
echo ""

echo -e "${GREEN}✅ Inicialización completada${NC}"
echo ""
echo "📝 Comandos útiles:"
echo "   Ver logs:     docker compose logs -f enertrack"
echo "   Reiniciar:    docker compose restart"
echo "   Detener:      docker compose down"
echo ""
