# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -fPIC -Wall -Wextra -O3 -Iinclude
LDFLAGS := -shared

# Директории
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
BIN_DIR := bin

# Исходные файлы
UTILS_SOURCES := $(SRC_DIR)/cipherUtils.cpp $(SRC_DIR)/fileProcessor.cpp
CIPHER_SOURCES := $(SRC_DIR)/atbashCipher.cpp $(SRC_DIR)/codeWordCipher.cpp $(SRC_DIR)/binarySequenceCipher.cpp
MAIN_SOURCE := $(SRC_DIR)/main.cpp

# Объектные файлы
UTILS_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(UTILS_SOURCES))
ATBASH_OBJ := $(BUILD_DIR)/atbashCipher.o
CODEWORD_OBJ := $(BUILD_DIR)/codeWordCipher.o
BINARYSEQ_OBJ := $(BUILD_DIR)/binarySequenceCipher.o
MAIN_OBJ := $(BUILD_DIR)/main.o

# Целевые библиотеки
LIB_UTILS := $(LIB_DIR)/libcrypto_utils.so
LIB_ATBASH := $(LIB_DIR)/libatbash.so
LIB_CODEWORD := $(LIB_DIR)/libcodeword.so
LIB_BINARYSEQ := $(LIB_DIR)/libbinaryseq.so
APP := $(BIN_DIR)/crypto_app

.PHONY: all clean

all: $(LIB_UTILS) $(LIB_ATBASH) $(LIB_CODEWORD) $(LIB_BINARYSEQ) $(APP)

# Библиотека утилит
$(LIB_UTILS): $(UTILS_OBJS)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

# Библиотека Atbash
$(LIB_ATBASH): $(ATBASH_OBJ)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^ -L$(LIB_DIR) -lcrypto_utils

# Библиотека CodeWord
$(LIB_CODEWORD): $(CODEWORD_OBJ)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^ -L$(LIB_DIR) -lcrypto_utils

# Библиотека BinarySequence
$(LIB_BINARYSEQ): $(BINARYSEQ_OBJ)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^ -L$(LIB_DIR) -lcrypto_utils

$(APP): $(MAIN_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $^ -L$(LIB_DIR) -latbash -lcodeword -lbinaryseq -lcrypto_utils -Wl,-rpath='$$ORIGIN/../lib'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)