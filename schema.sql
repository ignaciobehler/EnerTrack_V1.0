-- Schema para EnerTrack - Base de datos medidoresEnergia

-- Tabla de Usuarios
CREATE TABLE IF NOT EXISTS `Usuarios` (
  `usuario_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `nombreUsuario` VARCHAR(100) NOT NULL UNIQUE,
  `password_hash` VARCHAR(255) NOT NULL,
  `telegram_chat_id` BIGINT DEFAULT NULL,
  `telegram_vinculado` TINYINT(1) DEFAULT 0,
  `codigo_vinculacion` VARCHAR(50) DEFAULT NULL,
  `fecha_registro` DATETIME DEFAULT CURRENT_TIMESTAMP(),
  PRIMARY KEY (`usuario_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Tabla de Nodos
CREATE TABLE IF NOT EXISTS `Nodos` (
  `nodo_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `esp_id` VARCHAR(50) NOT NULL UNIQUE,
  `nombre` VARCHAR(100) DEFAULT NULL,
  `descripcion` TEXT DEFAULT NULL,
  `activo` TINYINT(1) NOT NULL DEFAULT 1,
  `fecha_creacion` DATETIME DEFAULT CURRENT_TIMESTAMP(),
  PRIMARY KEY (`nodo_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Tabla de relación Usuarios-Nodos (muchos a muchos)
CREATE TABLE IF NOT EXISTS `UsuariosNodos` (
  `usuario_id` INT(10) UNSIGNED NOT NULL,
  `nodo_id` INT(10) UNSIGNED NOT NULL,
  `activo` TINYINT(1) NOT NULL DEFAULT 1,
  `ubicacion` VARCHAR(100) DEFAULT NULL,
  `fecha_asignacion` DATETIME DEFAULT CURRENT_TIMESTAMP(),
  `ultimo_acceso` DATETIME DEFAULT NULL,
  PRIMARY KEY (`usuario_id`, `nodo_id`),
  FOREIGN KEY (`usuario_id`) REFERENCES Usuarios(usuario_id) ON DELETE CASCADE,
  FOREIGN KEY (`nodo_id`) REFERENCES Nodos(nodo_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Tabla de Umbrales de Nodos para alertas de Telegram
CREATE TABLE IF NOT EXISTS `UmbralesNodo` (
  `id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `usuario_id` INT(10) UNSIGNED NOT NULL,
  `nodo_id` INT(10) UNSIGNED NOT NULL,
  `umbral_kw` DECIMAL(10,3) DEFAULT NULL,
  `alertas_activas` TINYINT(1) DEFAULT 1,
  `fecha_actualizacion` DATETIME DEFAULT CURRENT_TIMESTAMP() ON UPDATE CURRENT_TIMESTAMP(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_usuario_nodo` (`usuario_id`, `nodo_id`),
  FOREIGN KEY (`usuario_id`) REFERENCES Usuarios(usuario_id) ON DELETE CASCADE,
  FOREIGN KEY (`nodo_id`) REFERENCES Nodos(nodo_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
