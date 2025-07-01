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

# Создание директорий
mkdir -p "$LIB_DIR"
mkdir -p "$INC_DIR"
mkdir -p "$BIN_DIR"

# Копирование библиотек
cp lib/libcrypto_utils.so "$LIB_DIR"

# Копирование заголовочных файлов
cp include/*.h "$INC_DIR"

# Копирование исполняемого файла
cp bin/crypto_app "$BIN_DIR"

# Обновление кэша динамических библиотек
ldconfig

echo "Установка завершена:"
echo " - Библиотеки: $LIB_DIR"
echo " - Заголовки: $INC_DIR"
echo " - Исполняемый файл: $BIN_DIR"