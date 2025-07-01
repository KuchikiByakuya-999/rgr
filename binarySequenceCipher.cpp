#include "ciphers.h"
#include "fileProcessor.h"
#include <stdexcept>

using namespace std;

string encodeBinary(const string& binary) {
    if (!isBinaryString(binary)) {
        throw invalid_argument("Входная строка должна содержать только 0 и 1");
    }
    
    if (binary.empty()) {
        return "";
    }
    
    string result;
    result += binary[0];
    
    for (size_t i = 1; i < binary.size(); i++) {
        if (binary[i] == binary[i - 1]) {
            result += '1';
        } else {
            result += '0';
        }
    }
    
    return result;
}

string decodeBinary(const string& encoded) {
    if (!isBinaryString(encoded)) {
        throw invalid_argument("Входная строка должна содержать только 0 и 1");
    }
    
    if (encoded.empty()) {
        return "";
    }
    
    string result;
    result += encoded[0];
    
    for (size_t i = 1; i < encoded.size(); i++) {
        if (encoded[i] == '1') {
            result += result[i - 1];
        } else {
            result += (result[i - 1] == '0' ? '1' : '0');
        }
    }
    
    return result;
}

void encodeFileBinary(const string& inputPath, const string& outputPath) {
    auto processor = [](const string& line) {
        return encodeBinary(line);
    };
    processLargeFile(inputPath, outputPath, processor);
}

void decodeFileBinary(const string& inputPath, const string& outputPath) {
    auto processor = [](const string& line) {
        return decodeBinary(line);
    };
    processLargeFile(inputPath, outputPath, processor);
}