#include "ciphers.h"
#include "fileProcessor.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

string encryptAtbash(const string& text) {
    string result;
    
    vector<pair<unsigned char, unsigned char>> ranges = {
        {0x41, 0x5A},   // A-Z
        {0x61, 0x7A},    // a-z
        {0x30, 0x39},   // 0-9
        {0xC0, 0xDF},    // А-Я (кроме Ё)
        {0xE0, 0xFF}     // а-я (кроме ё)
    };
    
    unordered_map<unsigned char, unsigned char> specialMap = {
        {0x81, 0xD5},  // Ё (0x81) → Х (0xD5)
        {0xB8, 0xF5},  // ё (0xB8) → х (0xF5)
        {0xD5, 0x81},  // Х (0xD5) → Ё (0x81)
        {0xF5, 0xB8},   // х (0xF5) → ё (0xB8)
        
        {' ', ' '},
        {'-', '-'},
        {'#', '#'}
    };
    
    for (unsigned char c : text) {
        bool processed = false;
        
        // Сначала проверяем спецсимволы
        if (specialMap.find(c) != specialMap.end()) {
            result += specialMap[c];
            continue;
        }
        
        // Затем проверяем диапазоны
        for (const auto& range : ranges) {
            if (c >= range.first && c <= range.second) {
                char mirrored = range.second - (c - range.first);
                result += mirrored;
                processed = true;
                break;
            }
        }
        
        // Если символ не обработан – оставляем как есть (не инвертируем!)
        if (!processed) {
            result += c;
        }
    }
    
    return result;
}

string decryptAtbash(const string& text) {
    return encryptAtbash(text);
}

// Остальные функции остаются без изменений
void encryptFileAtbash(const string& inputPath, const string& outputPath) {
    processLargeFile(inputPath, outputPath, encryptAtbash);
}

void decryptFileAtbash(const string& inputPath, const string& outputPath) {
    encryptFileAtbash(inputPath, outputPath);
}

void encryptBinaryAtbash(const string& inputPath, const string& outputPath) {
    auto processor = [](const vector<char>& data) {
        string text(data.begin(), data.end());
        string encrypted = encryptAtbash(text);
        return vector<char>(encrypted.begin(), encrypted.end());
    };
    processBinaryFile(inputPath, outputPath, processor);
}

void decryptBinaryAtbash(const string& inputPath, const string& outputPath) {
    encryptBinaryAtbash(inputPath, outputPath);
}