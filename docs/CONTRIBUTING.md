# 🤝 Contribuyendo a EnerTrack

¡Gracias por tu interés en contribuir a EnerTrack! Este documento te guiará en el proceso.

## 📋 Tabla de Contenidos

- [Código de Conducta](#código-de-conducta)
- [Cómo Puedo Contribuir](#cómo-puedo-contribuir)
- [Configuración del Entorno de Desarrollo](#configuración-del-entorno-de-desarrollo)
- [Proceso de Pull Request](#proceso-de-pull-request)
- [Guía de Estilo](#guía-de-estilo)

## 📜 Código de Conducta

Este proyecto se adhiere a un código de conducta. Al participar, se espera que mantengas este código.

- Sé respetuoso y considerado con otros colaboradores
- Usa lenguaje inclusivo y acogedor
- Acepta críticas constructivas con gracia
- Enfócate en lo mejor para la comunidad

## 🚀 Cómo Puedo Contribuir

### Reportar Bugs

Si encuentras un bug:

1. **Verifica** que el bug no haya sido reportado antes en [Issues](../../issues)
2. **Crea un issue** con:
   - Título descriptivo
   - Descripción detallada del problema
   - Pasos para reproducir
   - Comportamiento esperado vs actual
   - Logs relevantes
   - Información del sistema (OS, Docker version, etc.)

### Sugerir Mejoras

Para sugerir nuevas características:

1. **Abre un issue** con la etiqueta `enhancement`
2. **Describe** claramente la funcionalidad
3. **Explica** por qué sería útil para el proyecto
4. **Proporciona ejemplos** de uso si es posible

### Contribuir con Código

1. **Fork** el repositorio
2. **Crea una rama** para tu feature: `git checkout -b feature/nueva-funcionalidad`
3. **Haz commit** de tus cambios: `git commit -am 'Add: nueva funcionalidad'`
4. **Push** a la rama: `git push origin feature/nueva-funcionalidad`
5. **Abre un Pull Request**

## ⚙️ Configuración del Entorno de Desarrollo

### Requisitos

- Docker y Docker Compose
- Python 3.11+
- Git

### Setup

```bash
# Clonar el repositorio
git clone https://github.com/TU_USUARIO/enertrack.git
cd enertrack

# Copiar variables de entorno
cp .env.example .env

# Editar .env con tus valores de desarrollo
nano .env

# Crear red Docker
docker network create docker_iot-1_default

# Iniciar servicios
docker compose up -d

# Ver logs
docker compose logs -f enertrack
```

### Testing Local

```bash
# Verificar servicios
docker compose ps

# Ver logs de un servicio específico
docker compose logs -f enertrack

# Reiniciar un servicio
docker compose restart enertrack

# Detener todos los servicios
docker compose down
```

## 📝 Proceso de Pull Request

1. **Actualiza tu fork** con la rama principal:
   ```bash
   git checkout main
   git pull upstream main
   ```

2. **Crea una rama** descriptiva:
   ```bash
   git checkout -b feature/descripcion-corta
   ```

3. **Haz tus cambios** siguiendo la guía de estilo

4. **Prueba tus cambios** localmente:
   ```bash
   docker compose build enertrack
   docker compose up -d enertrack
   docker compose logs -f enertrack
   ```

5. **Commit** con mensajes descriptivos:
   ```bash
   git commit -m "Add: nueva funcionalidad X"
   ```

6. **Push** a tu fork:
   ```bash
   git push origin feature/descripcion-corta
   ```

7. **Abre un Pull Request** en GitHub con:
   - Título claro y conciso
   - Descripción detallada de los cambios
   - Referencias a issues relacionados
   - Screenshots si aplica

## 🎨 Guía de Estilo

### Python (Backend)

- **PEP 8**: Seguir estándar de Python
- **Nombres**: snake_case para funciones y variables
- **Clases**: PascalCase
- **Constantes**: UPPER_CASE
- **Indentación**: 4 espacios
- **Imports**: Agrupar en orden: stdlib, third-party, local

```python
# ✅ Bueno
def calcular_consumo_total(nodo_id: int) -> float:
    """Calcula el consumo total de un nodo."""
    pass

# ❌ Malo
def CalcularConsumo(nodoid):
    pass
```

### Mensajes de Commit

Formato: `<tipo>: <descripción corta>`

Tipos:
- `Add`: Nueva funcionalidad
- `Fix`: Corrección de bug
- `Update`: Actualización de funcionalidad existente
- `Refactor`: Refactorización de código
- `Docs`: Cambios en documentación
- `Style`: Cambios de formato (sin afectar lógica)
- `Test`: Agregar o modificar tests
- `Chore`: Tareas de mantenimiento

```bash
# ✅ Buenos ejemplos
git commit -m "Add: endpoint para obtener datos históricos"
git commit -m "Fix: error al calcular promedio de consumo"
git commit -m "Docs: actualizar guía de instalación"

# ❌ Malos ejemplos
git commit -m "cambios"
git commit -m "fix bug"
git commit -m "WIP"
```

### Docker y Docker Compose

- **Imágenes**: Usar versiones específicas, no `latest`
- **Variables**: Siempre usar archivo `.env`
- **Volúmenes**: Usar rutas relativas para portabilidad
- **Networks**: Documentar networks necesarias

### Documentación

- **README**: Mantener actualizado con cambios mayores
- **Comentarios**: Código Python debe tener docstrings
- **Issues**: Usar templates y etiquetas apropiadas
- **DEPLOY.md**: Actualizar si cambias configuración de servicios

## 🐛 Debugging

### Logs de servicios

```bash
# Todos los servicios
docker compose logs -f

# Servicio específico
docker compose logs -f enertrack

# Últimas 100 líneas
docker compose logs --tail=100 enertrack
```

### Inspeccionar contenedor

```bash
# Entrar al contenedor
docker exec -it enertrack bash

# Ver procesos
docker top enertrack

# Estadísticas de recursos
docker stats enertrack
```

### Base de datos

```bash
# Conectar a MariaDB
docker exec -it mariadb mariadb -u medidor_user -p medidoresEnergia

# Ver tablas
SHOW TABLES;

# Verificar datos
SELECT * FROM Usuarios;
```

## 📚 Recursos Adicionales

- [Documentación de Flask](https://flask.palletsprojects.com/)
- [Documentación de Docker Compose](https://docs.docker.com/compose/)
- [InfluxDB Documentation](https://docs.influxdata.com/)
- [Mosquitto MQTT Broker](https://mosquitto.org/documentation/)
- [Telegram Bot API](https://core.telegram.org/bots/api)

## ❓ Preguntas

Si tienes preguntas:

1. Revisa la [documentación existente](README.md)
2. Busca en [Issues cerrados](../../issues?q=is%3Aissue+is%3Aclosed)
3. Abre un [nuevo issue](../../issues/new) con la etiqueta `question`

---

¡Gracias por contribuir a EnerTrack! 🎉
