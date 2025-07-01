#include "fileProcessor.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

string readTextFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filePath);
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeTextToFile(const string& filePath, const string& content) {
    ofstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filePath);
    }
    
    file << content;
}

void processLargeFile(const string& inputPath, const string& outputPath, 
                       function<string(const string&)> processor) {
    ifstream input_file(inputPath);
    if (!input_file.is_open()) {
        throw runtime_error("Не удалось открыть входной файл: " + inputPath);
    }
    
    ofstream output_file(outputPath);
    if (!output_file.is_open()) {
        throw runtime_error("Не удалось открыть выходной файл: " + outputPath);
    }
    
    string line;
    while (getline(input_file, line)) {
        output_file << processor(line) << "\n";
    }
}

vector<char> readBinaryFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filePath);
    }
    
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);
    
    vector<char> buffer(size);
    file.read(buffer.data(), size);
    return buffer;
}

void writeBinaryFile(const string& filePath, const vector<char>& data) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filePath);
    }
    
    file.write(data.data(), data.size());
}

void processBinaryFile(const string& inputPath, const string& outputPath,
                        function<vector<char>(const vector<char>&)> processor) {
    auto input_data = readBinaryFile(inputPath);
    auto output_data = processor(input_data);
    writeBinaryFile(outputPath, output_data);
}

void processImage(const string& inputPath, const string& outputPath, bool encrypt) {
    ifstream input(inputPath, ios::binary);
    ofstream output(outputPath, ios::binary);
    
    if (!input.is_open()) {
        throw runtime_error("Не удалось открыть входной файл: " + inputPath);
    }
    
    if (!output.is_open()) {
        throw runtime_error("Не удалось открыть выходной файл: " + outputPath);
    }
    
    // Копируем заголовок (первые 54 байта для BMP) без изменений
    vector<char> header(54);
    input.read(header.data(), 54);
    output.write(header.data(), 54);
    
    // Обрабатываем пиксельные данные
    char pixel[3];
    while (input.read(pixel, 3)) {
        if (encrypt) {
            pixel[0] = ~pixel[0];
            pixel[1] = ~pixel[1];
            pixel[2] = ~pixel[2];
        } else {
            pixel[0] = ~pixel[0];
            pixel[1] = ~pixel[1];
            pixel[2] = ~pixel[2];
        }
        output.write(pixel, 3);
    }
}