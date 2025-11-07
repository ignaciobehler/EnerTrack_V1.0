# ✅ Checklist para Subir a GitHub

## Antes de subir el repositorio

### 1. Verificar que archivos sensibles estén excluidos

- [ ] Verificar `.gitignore` contiene:
  ```
  .env
  mariadb/
  influxdb/data/
  influxdb/config/
  swag/
  mosquitto/config/duckdns.ini
  __pycache__/
  *.pyc
  *.log
  ```

- [ ] Confirmar que `.env` NO está versionado:
  ```bash
  git status | grep .env
  # No debe aparecer .env, solo .env.example
  ```

### 2. Verificar archivos importantes están incluidos

- [ ] `compose.yaml` - Configuración Docker Compose completa
- [ ] `.env.example` - Plantilla de variables de entorno (sin datos reales)
- [ ] `README.md` - Documentación principal del proyecto
- [ ] `DEPLOY.md` - Guía de despliegue paso a paso
- [ ] `schema.sql` - Schema de la base de datos
- [ ] `init.sh` - Script de inicialización
- [ ] `generate_keys.py` - Generador de claves secretas
- [ ] `enertrack/` - Código fuente de la aplicación
- [ ] `requirements.txt` - Dependencias Python

### 3. Verificar que NO se suban datos sensibles

- [ ] NO incluir `mariadb/` (datos de la base de datos)
- [ ] NO incluir `influxdb/data/` (datos de series temporales)
- [ ] NO incluir `.env` (variables con valores reales)
- [ ] NO incluir `swag/` (certificados SSL)
- [ ] NO incluir `mosquitto/config/duckdns.ini` (token DuckDNS)

### 4. Limpiar tokens y passwords del código

- [ ] Buscar tokens hardcodeados:
  ```bash
  grep -r "AAH" enertrack/
  grep -r "password" enertrack/
  grep -r "token" enertrack/
  ```

- [ ] Reemplazar cualquier token/password hardcodeado con variables de entorno

### 5. Verificar archivos de documentación

- [ ] `README.md` está completo con:
  - Descripción del proyecto
  - Arquitectura
  - Instrucciones de instalación rápida
  - Configuración de servicios
  - Solución de problemas

- [ ] `DEPLOY.md` tiene instrucciones detalladas de despliegue desde cero

### 6. Testing local

- [ ] Probar despliegue limpio en directorio temporal:
  ```bash
  cd /tmp
  git clone /home/iot/enertrack test_deploy
  cd test_deploy
  cp .env.example .env
  # Editar .env con valores de prueba
  docker network create docker_iot-1_default
  docker compose up -d
  docker compose ps
  docker compose down
  cd /home/iot/enertrack
  rm -rf /tmp/test_deploy
  ```

## Inicializar Git

### 7. Configurar Git (si es primera vez)

```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu@email.com"
```

### 8. Inicializar repositorio

```bash
cd /home/iot/enertrack
git init
```

### 9. Agregar archivos

```bash
# Agregar todos los archivos (respetando .gitignore)
git add .

# Verificar qué se va a subir
git status

# Verificar que .env NO aparezca
# Verificar que mariadb/ influxdb/data/ NO aparezcan
```

### 10. Primer commit

```bash
git commit -m "Initial commit: EnerTrack - Sistema IoT de monitoreo energético

- Docker Compose con 7 servicios (MariaDB, InfluxDB, Mosquitto, SWAG, PHPMyAdmin, ClienteMQTT, EnerTrack)
- Aplicación Flask con dashboard de monitoreo en tiempo real
- Bot de Telegram integrado para alertas
- MQTT con SSL/TLS
- Certificados automáticos con Let's Encrypt vía DuckDNS
- Schema de base de datos incluido
- Scripts de inicialización y despliegue
- Documentación completa"
```

## Subir a GitHub

### 11. Crear repositorio en GitHub

1. Ve a https://github.com/new
2. Nombre: `enertrack`
3. Descripción: `Sistema IoT de monitoreo energético con ESP32, MQTT, InfluxDB y alertas por Telegram`
4. **Importante**: NO inicialices con README, .gitignore o LICENSE
5. Crear repositorio

### 12. Conectar repositorio local con GitHub

```bash
git remote add origin https://github.com/TU_USUARIO/enertrack.git
git branch -M main
git push -u origin main
```

### 13. Verificar en GitHub

- [ ] Verificar que todos los archivos se subieron correctamente
- [ ] Confirmar que `.env` NO está en el repositorio
- [ ] Confirmar que `mariadb/` NO está en el repositorio
- [ ] Confirmar que `influxdb/data/` NO está en el repositorio
- [ ] Verificar que `README.md` se ve correctamente

### 14. Agregar descripción y topics en GitHub

En la página del repositorio:
- [ ] Agregar descripción corta
- [ ] Agregar topics: `iot`, `mqtt`, `influxdb`, `docker`, `telegram-bot`, `esp32`, `flask`, `energy-monitoring`, `smart-home`
- [ ] Agregar Website (si aplica)

## Configurar repositorio

### 15. Crear archivo .github/workflows (Opcional - CI/CD)

- [ ] Configurar GitHub Actions para tests automáticos (opcional)

### 16. Crear LICENSE

- [ ] Agregar archivo LICENSE (MIT, GPL, etc.)

### 17. Agregar badges al README (Opcional)

```markdown
![Docker](https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white)
![Python](https://img.shields.io/badge/python-3.11-blue.svg)
![License](https://img.shields.io/github/license/TU_USUARIO/enertrack)
```

## Testing en VPS limpio

### 18. Clonar en otro servidor (prueba final)

- [ ] Clonar repositorio en VPS de prueba
- [ ] Seguir instrucciones de `DEPLOY.md`
- [ ] Verificar que todo funciona correctamente
- [ ] Documentar cualquier paso faltante

## Después de subir

### 19. Mantenimiento

- [ ] Actualizar README con badges de build status
- [ ] Crear wiki con documentación extendida
- [ ] Configurar Issues y Projects en GitHub
- [ ] Compartir con la comunidad

---

## ⚠️ IMPORTANTE - Seguridad

**NUNCA subas a GitHub:**
- Contraseñas reales
- Tokens de API/Telegram
- Certificados SSL privados
- Datos de producción (bases de datos)
- Archivos `.env` con valores reales

**Siempre verifica antes de cada push:**
```bash
git diff --cached
```

**Si accidentalmente subes datos sensibles:**
1. NO solo borres el archivo y hagas otro commit
2. Usa `git filter-branch` o `BFG Repo Cleaner` para eliminar del historial
3. Considera el token/password comprometido y cámbialo inmediatamente
4. Contacta a GitHub Support si es necesario

---

¡Listo para subir! 🚀
