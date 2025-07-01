#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include <vector>
#include <functional>

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;

string readTextFromFile(const string& filePath);
void writeTextToFile(const string& filePath, const string& content);
void processLargeFile(const string& inputPath, const string& outputPath, 
                       function<string(const string&)> processor);

vector<char> readBinaryFile(const string& filePath);
void writeBinaryFile(const string& filePath, const vector<char>& data);
void processBinaryFile(const string& inputPath, const string& outputPath,
                        function<vector<char>(const vector<char>&)> processor);

void processImage(const string& inputPath, const string& outputPath, bool encrypt);

#ifdef __cplusplus
}
#endif

#endif