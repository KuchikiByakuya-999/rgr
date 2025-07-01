#include "ciphers.h"
#include "fileProcessor.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <vector>
#include <locale>

using namespace std;

enum class Algorithm {
    ATBASH = 1,
    CODE_WORD = 2,
    BINARY_SEQUENCE = 3
};

enum class Action {
    ENCRYPT = 1,
    DECRYPT = 2
};

enum class Source {
    TEXT_INPUT = 1,
    FILE_INPUT = 2
};

enum class Mode {
    TEXT = 1,
    BINARY = 2
};

const string PASSWORD = "qwerty";

bool authenticate() {
    string input;
    cout << "Введите пароль для доступа к приложению: ";
    getline(cin, input);
    return input == PASSWORD;
}

int getIntInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Пожалуйста, введите число от " << min << " до " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

void handleAtbash(Action action, Source source, Mode mode) {
    if (mode == Mode::TEXT) {
        if (source == Source::TEXT_INPUT) {
            cout << "Введите текст: ";
            string text;
            getline(cin, text);
            string result = (action == Action::ENCRYPT) ? 
                encryptAtbash(text) : decryptAtbash(text);
            cout << "Результат: " << result << endl;
        } else {
            cout << "Введите путь к входному файлу: ";
            string inputPath;
            getline(cin, inputPath);
            cout << "Введите путь для выходного файла: ";
            string outputPath;
            getline(cin, outputPath);
            
            if (action == Action::ENCRYPT) {
                encryptFileAtbash(inputPath, outputPath);
            } else {
                decryptFileAtbash(inputPath, outputPath);
            }
            cout << "Файл успешно обработан" << endl;
        }
    } else {
        if (source == Source::TEXT_INPUT) {
            cout << "Бинарный режим доступен только для файлов" << endl;
            return;
        }
        
        cout << "Введите путь к входному файлу: ";
        string inputPath;
        getline(cin, inputPath);
        cout << "Введите путь для выходного файла: ";
        string outputPath;
        getline(cin, outputPath);
        
        if (action == Action::ENCRYPT) {
            encryptBinaryAtbash(inputPath, outputPath);
        } else {
            decryptBinaryAtbash(inputPath, outputPath);
        }
        cout << "Файл успешно обработан" << endl;
    }
}

void handleCodeWord(Action action, Source source, Mode mode) {
    cout << "Введите кодовое слово: ";
    string key;
    getline(cin, key);
    
    if (mode == Mode::TEXT) {
        if (source == Source::TEXT_INPUT) {
            cout << "Введите текст: ";
            string text;
            getline(cin, text);
            
            try {
                string result = (action == Action::ENCRYPT) ? 
                    encryptCodeWord(text, key) : decryptCodeWord(text, key);
                cout << "Результат: " << result << endl;
            } catch (const invalid_argument& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        } else {
            cout << "Введите путь к входному файлу: ";
            string inputPath;
            getline(cin, inputPath);
            cout << "Введите путь для выходного файла: ";
            string outputPath;
            getline(cin, outputPath);
            
            try {
                if (action == Action::ENCRYPT) {
                    encryptFileCodeWord(inputPath, outputPath, key);
                } else {
                    decryptFileCodeWord(inputPath, outputPath, key);
                }
                cout << "Файл успешно обработан" << endl;
            } catch (const invalid_argument& e) {
                cout << "Ошибка при обработке файла: " << e.what() << endl;
            }
        }
    } else {
        if (source == Source::TEXT_INPUT) {
            cout << "Бинарный режим доступен только для файлов" << endl;
            return;
        }
        
        cout << "Введите путь к входному файлу: ";
        string inputPath;
        getline(cin, inputPath);
        cout << "Введите путь для выходного файла: ";
        string outputPath;
        getline(cin, outputPath);
        
        try {
            if (action == Action::ENCRYPT) {
                encryptBinaryCodeWord(inputPath, outputPath, key);
            } else {
                decryptBinaryCodeWord(inputPath, outputPath, key);
            }
            cout << "Файл успешно обработан" << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка при обработке файла: " << e.what() << endl;
        }
    }
}

void handleBinarySequence(Action action, Source source, Mode mode) {
    if (mode == Mode::TEXT) {
        if (source == Source::TEXT_INPUT) {
            cout << "Введите последовательность нулей и единиц: ";
            string binary;
            getline(cin, binary);
            
            try {
                string result = (action == Action::ENCRYPT) ? 
                    encodeBinary(binary) : 
                    decodeBinary(binary);
                cout << "Результат: " << result << endl;
            } catch (const invalid_argument& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        } else {
            cout << "Введите путь к входному файлу: ";
            string inputPath;
            getline(cin, inputPath);
            cout << "Введите путь для выходного файла: ";
            string outputPath;
            getline(cin, outputPath);
            
            try {
                if (action == Action::ENCRYPT) {
                    encodeFileBinary(inputPath, outputPath);
                } else {
                    decodeFileBinary(inputPath, outputPath);
                }
                cout << "Файл успешно обработан" << endl;
            } catch (const invalid_argument& e) {
                cout << "Ошибка при обработке файла: " << e.what() << endl;
            }
        }
    } else {
        cout << "Данный алгоритм не поддерживает бинарный режим" << endl;
    }
}

void startUserInterface() {
    while (true) {
        cout << "\n=== Криптографическая система ===" << endl;
        cout << "1. Шифр Атбаш" << endl;
        cout << "2. Шифр с кодовым словом" << endl;
        cout << "3. Шифрование последовательностей нулей и единиц" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите алгоритм (1-4): ";
        
        int choice = getIntInput(1, 4);
        cout << endl;
        
        if (choice == 4) {
            cout << "Завершение работы..." << endl;
            break;
        }
        
        cout << "1. Шифрование" << endl;
        cout << "2. Дешифрование" << endl;
        cout << "Выберите действие (1-2): ";
        
        int action = getIntInput(1, 2);
        cout << endl;
        
        cout << "1. Ввод текста" << endl;
        cout << "2. Обработка файла" << endl;
        cout << "Выберите источник (1-2): ";
        
        int source = getIntInput(1, 2);
        cout << endl;
        
        cout << "1. Текстовый режим" << endl;
        cout << "2. Бинарный режим (для любых файлов)" << endl;
        cout << "Выберите режим работы (1-2): ";
        
        int mode = getIntInput(1, 2);
        cout << endl;
        
        switch (static_cast<Algorithm>(choice)) {
            case Algorithm::ATBASH:
                handleAtbash(static_cast<Action>(action), static_cast<Source>(source), static_cast<Mode>(mode));
                break;
            case Algorithm::CODE_WORD:
                handleCodeWord(static_cast<Action>(action), static_cast<Source>(source), static_cast<Mode>(mode));
                break;
            case Algorithm::BINARY_SEQUENCE:
                handleBinarySequence(static_cast<Action>(action), static_cast<Source>(source), static_cast<Mode>(mode));
                break;
        }
        
        cout << "\nНажмите Enter чтобы продолжить...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    try {
        if (!authenticate()) {
            cout << "Неверный пароль! Доступ запрещен." << endl;
            return 1;
        }
        
        startUserInterface();
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}