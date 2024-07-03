#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

void showSourceCode(const string& source) {
    cout << "Source Code:" << endl;
    cout << source << endl;
}

void performLexicalAnalysis(const string& source, vector<Token>& tokens) {
    Lexer lexer(source);
    tokens = lexer.tokenize();

    cout << "Lexical Analysis - Tokens:" << endl;
    for (const Token& token : tokens) {
        cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << endl;
    }
}

void performSyntaxAnalysis(const vector<Token>& tokens) {
    Parser parser(tokens);
    auto ast = parser.parse();

    if (ast != nullptr) {
        cout << "Syntax Analysis Complete" << endl;
    } else {
        cout << "Syntax Analysis Failed" << endl;
    }
}

int main() {
    string source = "int a; float b; a = 1 + 2; b = a + 3.5;";
    vector<Token> tokens;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Show Source Code" << endl;
        cout << "2. Perform Lexical Analysis" << endl;
        cout << "3. Perform Syntax Analysis" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                showSourceCode(source);
                break;
            case 2:
                performLexicalAnalysis(source, tokens);
                break;
            case 3:
                if (tokens.empty()) {
                    cout << "Please perform lexical analysis first." << endl;
                } else {
                    performSyntaxAnalysis(tokens);
                }
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}

