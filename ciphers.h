// ciphers.h
#ifndef CIPHERS_H
#define CIPHERS_H

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

bool isBinaryString(const std::string& input);
void validateKey(const std::string& key);

std::string encryptCodeWord(const std::string& text, const std::string& key);
std::string decryptCodeWord(const std::string& text, const std::string& key);
void encryptFileCodeWord(const std::string& inputPath, const std::string& outputPath, const std::string& key);
void decryptFileCodeWord(const std::string& inputPath, const std::string& outputPath, const std::string& key);
void encryptBinaryCodeWord(const std::string& inputPath, const std::string& outputPath, const std::string& key);
void decryptBinaryCodeWord(const std::string& inputPath, const std::string& outputPath, const std::string& key);

// Binary Sequence Cipher
std::string encodeBinary(const std::string& binary);
std::string decodeBinary(const std::string& encoded);
void encodeFileBinary(const std::string& inputPath, const std::string& outputPath);
void decodeFileBinary(const std::string& inputPath, const std::string& outputPath);

// Atbash Cipher
std::string encryptAtbash(const std::string& text);
std::string decryptAtbash(const std::string& text);
void encryptFileAtbash(const std::string& inputPath, const std::string& outputPath);
void decryptFileAtbash(const std::string& inputPath, const std::string& outputPath);
void encryptBinaryAtbash(const std::string& inputPath, const std::string& outputPath);
void decryptBinaryAtbash(const std::string& inputPath, const std::string& outputPath);

#ifdef __cplusplus
}
#endif

#endif