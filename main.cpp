#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "ASTNode.h"

using namespace std;

// Función para imprimir el AST (para depuración).
void printAST(shared_ptr<ASTNode> node, int indent = 0) {
    if (node == nullptr) return;
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << node->value << endl;
    printAST(node->left, indent + 1);
    printAST(node->right, indent + 1);
}

int main() {
    string sourceCode = "int a; float b; c = a + b;";
    Lexer lexer(sourceCode);
    vector<Token> tokens = lexer.tokenize();

    cout << "Tokens:" << endl;
    for (const Token& token : tokens) {
        cout << token.value << " ";
    }
    cout << endl;

    Parser parser(tokens);
    try {
        shared_ptr<ASTNode> ast = parser.parse();
        cout << "AST:" << endl;
        printAST(ast);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

