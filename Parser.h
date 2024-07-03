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
    // Constructor que inicializa el parser con los tokens.
    Parser(const vector<Token>& tokens) : tokens(tokens), current(0) {}

    // Función que inicia el proceso de parsing.
    shared_ptr<ASTNode> parse();

private:
    vector<Token> tokens; // La serie de tokens.
    size_t current; // La posición actual en la serie de tokens.

    // Función que analiza una declaración.
    shared_ptr<ASTNode> parseDeclaration();

    // Función que analiza una expresión.
    shared_ptr<ASTNode> parseExpression();

    // Función que analiza una expresión primaria.
    shared_ptr<ASTNode> parsePrimary();

    // Función que analiza una operación binaria.
    shared_ptr<ASTNode> parseBinaryOp(int precedence, shared_ptr<ASTNode> left);

    // Función que verifica si hemos llegado al final de los tokens.
    bool isAtEnd() const;

    // Función que obtiene el token actual.
    Token advance();

    // Función que obtiene el token actual sin avanzar.
    Token peek() const;

    // Función que obtiene el siguiente token sin avanzar.
    Token peekNext() const;

    // Función que consume un token esperado.
    Token consume(TokenType type, const string& message);

    // Función que verifica si el token actual es del tipo esperado.
    bool check(TokenType type) const;

    // Función que verifica si el token actual es del tipo esperado y avanza.
    bool match(TokenType type);
};

#endif

