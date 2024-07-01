
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <iostream>
#include "Lexer.h"
#include "Parser.h"
//#include "SymbolTable.h"

using namespace std;

void showSourceCode(const string& source) {
    cout << "Codigo fuente:" << endl;
    cout << source << endl;
}

void performLexicalAnalysis(const string& source, vector<Token>& tokens) {
    Lexer lexer(source);
    tokens = lexer.tokenize();

    cout << "Analisis léxico - Tokens:" << endl;
    for (const Token& token : tokens) {
        cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << endl;
    }
}

void performSyntaxAnalysis(const vector<Token>& tokens, SymbolTable& symTable) {
    Parser parser(tokens, symTable);
    parser.parse();

    cout << "Analisis de sintaxis completo" << endl;
}

int main() {
	////
	
	
    string source = "int main() { int x = 0; return x; }";			///LO QUE VA A LEER
    
	
	///
	vector<Token> tokens;
    SymbolTable symTable;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Mostrar codigo fuente" << endl;
        cout << "2. Realizar análisis lexico" << endl;
        cout << "3. Realizar analisis de sintaxis" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion :  ";

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
                    cout << "Realice primero el análisis lexico." << endl;
                } else {
                    performSyntaxAnalysis(tokens, symTable);
                }
                break;
            case 4:
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "Opcion invalida. Intenta denuevo :D." << endl;
        }
    }

    return 0;
}

