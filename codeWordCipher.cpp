#include "ciphers.h"
#include "fileProcessor.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <iomanip>

using namespace std;

static wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;

string encryptCodeWord(const string& text, const string& key) {
    if (key.empty()) throw invalid_argument("Ключ не может быть пустым");
    if (text.empty()) return "";

    try {
        u32string u32text = converter.from_bytes(text);
        u32string u32key = converter.from_bytes(key);
        
        if (u32key.empty()) u32key = U" ";

        u32string result;
        result.reserve(u32text.size());

        for (size_t i = 0; i < u32text.size(); ++i) {
            char32_t text_char = u32text[i];
            char32_t key_char = u32key[i % u32key.size()];
            
            // Безопасное шифрование с сохранением символов
            char32_t encrypted_char;
            
            // Для кириллицы (U+0400-U+04FF)
            if (text_char >= 0x0400 && text_char <= 0x04FF) {
                encrypted_char = 0x0400 + ((text_char - 0x0400 + (key_char % 64)) % 256);
            }
            // Для ASCII (0-127)
            else if (text_char <= 127) {
                encrypted_char = (text_char + (key_char % 32)) % 128;
            }
            // Для остальных символов - оставляем как есть
            else {
                encrypted_char = text_char;
            }
            
            result.push_back(encrypted_char);
        }

        return converter.to_bytes(result);
    } catch (const exception& e) {
        throw runtime_error("Ошибка шифрования: " + string(e.what()));
    }
}

string decryptCodeWord(const string& text, const string& key) {
    if (key.empty()) throw invalid_argument("Ключ не может быть пустым");
    if (text.empty()) return "";

    try {
        u32string u32text = converter.from_bytes(text);
        u32string u32key = converter.from_bytes(key);
        
        if (u32key.empty()) u32key = U" ";

        u32string result;
        result.reserve(u32text.size());

        for (size_t i = 0; i < u32text.size(); ++i) {
            char32_t text_char = u32text[i];
            char32_t key_char = u32key[i % u32key.size()];
            
            char32_t decrypted_char;
            
            // Для кириллицы (U+0400-U+04FF)
            if (text_char >= 0x0400 && text_char <= 0x04FF) {
                decrypted_char = 0x0400 + ((text_char - 0x0400 - (key_char % 64) + 256) % 256);
            }
            // Для ASCII (0-127)
            else if (text_char <= 127) {
                decrypted_char = (text_char - (key_char % 32) + 128) % 128;
            }
            // Для остальных символов - оставляем как есть
            else {
                decrypted_char = text_char;
            }
            
            result.push_back(decrypted_char);
        }

        return converter.to_bytes(result);
    } catch (const exception& e) {
        throw runtime_error("Ошибка дешифрования: " + string(e.what()));
    }
}


// Остальные функции без изменений
void encryptFileCodeWord(const string& inputPath, const string& outputPath, const string& key) {
    auto processor = [&key](const string& line) {
        return encryptCodeWord(line, key);
    };
    processLargeFile(inputPath, outputPath, processor);
}

void decryptFileCodeWord(const string& inputPath, const string& outputPath, const string& key) {
    auto processor = [&key](const string& line) {
        return decryptCodeWord(line, key);
    };
    processLargeFile(inputPath, outputPath, processor);
}

void encryptBinaryCodeWord(const string& inputPath, const string& outputPath, const string& key) {
    auto processor = [&key](const vector<char>& data) {
        string text(data.begin(), data.end());
        string encrypted = encryptCodeWord(text, key);
        return vector<char>(encrypted.begin(), encrypted.end());
    };
    processBinaryFile(inputPath, outputPath, processor);
}

void decryptBinaryCodeWord(const string& inputPath, const string& outputPath, const string& key) {
    auto processor = [&key](const vector<char>& data) {
        string text(data.begin(), data.end());
        string decrypted = decryptCodeWord(text, key);
        return vector<char>(decrypted.begin(), decrypted.end());
    };
    processBinaryFile(inputPath, outputPath, processor);
}