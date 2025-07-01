#!/bin/bash

# Проверка прав root
if [ "$(id -u)" -ne 0 ]; then
    echo "Этот скрипт требует прав root. Используйте sudo."
    exit 1
fi

# Пути установки
PREFIX="/usr/local"
LIB_DIR="$PREFIX/lib"
INC_DIR="$PREFIX/include/crypto"
BIN_DIR="$PREFIX/bin"

# Удаление файлов
rm -f "$LIB_DIR/libcrypto_utils.so"
rm -f "$LIB_DIR/libcrypto_ciphers.so"
rm -f "$BIN_DIR/crypto_app"
rm -rf "$INC_DIR"

# Обновление кэша динамических библиотек
ldconfig

echo "Удаление завершено"