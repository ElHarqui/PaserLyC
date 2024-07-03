#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

void runLexer(const string& source) {
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    for (const Token& token : tokens) {
        cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << endl;
    }
}

void runParser(const string& source) {
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    shared_ptr<ASTNode> ast = parser.parse();

    cout << "Syntax Analysis Complete" << endl;
}

string readFile(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    int choice;
    string filename;

    while (true) {
        cout << "Choose an option: " << endl;
        cout << "1. Run Lexer and Run Parser" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;

        if (choice == 3) break;

        cout << "Enter the source file name: ";
        cin >> filename;

        string source = readFile(filename);

        switch (choice) {
            case 1:
                runLexer(source);
                runParser(source);
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}

