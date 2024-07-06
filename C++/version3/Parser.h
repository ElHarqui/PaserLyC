#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "ASTNode.h"

using namespace std;

// La clase Parser es responsable de convertir una serie de tokens en un árbol de sintaxis abstracta (AST).
class Parser {
public:
    // Constructor que inicializa el parser con una lista de tokens.
    Parser(const vector<Token>& tokens);

    // Función para parsear todos los tokens en un AST.
    // Devuelve un puntero compartido al nodo raíz del AST.
    shared_ptr<ASTNode> parse();

private:
    vector<Token> tokens; // La lista de tokens a parsear.
    size_t current; // La posición actual en la lista de tokens.

    // Función para avanzar al siguiente token.
    Token advance();

    // Función para obtener el token actual sin avanzar la posición.
    Token peek() const;

    // Función para verificar si el parser ha llegado al final de los tokens.
    bool isAtEnd() const;

    // Función para parsear una declaración.
    shared_ptr<ASTNode> parseStatement();

    // Función para parsear una expresión.
    shared_ptr<ASTNode> parseExpression();

    // Función para parsear un término (parte de una expresión).
    shared_ptr<ASTNode> parseTerm();

    // Función para parsear un factor (parte de un término).
    shared_ptr<ASTNode> parseFactor();
};

#endif

