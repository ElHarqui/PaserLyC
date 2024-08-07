#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

string readFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Archivo no se puede abrir");
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void runLexer(const string &source) {
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    for (const auto &token : tokens) {
        cout << "Tipo de Token: " << static_cast<int>(token.type) << ", Valor: " << token.value << endl;
    }
}

void runParser(const string &source) {
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    try {
        auto ast = parser.parse();
        cout << "Parseo satisfactorio!" << endl;
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    while (true) {
        cout << "Elije una opcion:" << endl;
        cout << "1. Correr Analisis Lexico" << endl;
        cout << "2. Correr Parser" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 3) break;

        cout << "Nombre de archivo : ";
        string filename;
        cin >> filename;

        string source;
        try {
            source = readFile(filename);
        } catch (const exception &e) {
            cout << e.what() << endl;
            continue;
        }

        if (choice == 1) {
            runLexer(source);
        } else if (choice == 2) {
            runParser(source);
        }
    }
    return 0;
}

