#!/usr/bin/env python3
"""
Script para generar claves secretas para EnerTrack
"""

import secrets
from cryptography.fernet import Fernet

print("🔐 Generando claves secretas para EnerTrack\n")
print("=" * 60)

# Flask Secret Key
flask_secret = secrets.token_urlsafe(32)
print(f"\nFLASK_SECRET_KEY={flask_secret}")

# Fernet Key
fernet_key = Fernet.generate_key().decode()
print(f"FERNET_KEY={fernet_key}")

# Password seguro aleatorio
password = secrets.token_urlsafe(16)
print(f"\nPassword aleatorio: {password}")

print("\n" + "=" * 60)
print("\n✅ Copia estos valores a tu archivo .env\n")
