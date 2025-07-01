#include "ciphers.h"
#include <regex>

using namespace std;

bool isBinaryString(const string& input) {
    return regex_match(input, regex("[01]+"));
}

void validateKey(const string& key) {
    if (key.empty()) {
        throw invalid_argument("Ключ не может быть пустым");
    }
}