#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "ASTNode.h"

using namespace std;

// La clase Parser es responsable de convertir una serie de tokens en un �rbol de sintaxis abstracta (AST).
class Parser {
public:
    // Constructor que inicializa el parser con los tokens.
    Parser(const vector<Token>& tokens) : tokens(tokens), current(0) {}

    // Funci�n que inicia el proceso de parsing.
    shared_ptr<ASTNode> parse();

private:
    vector<Token> tokens; // La serie de tokens.
    size_t current; // La posici�n actual en la serie de tokens.

    // Funci�n que analiza una declaraci�n.
    shared_ptr<ASTNode> parseDeclaration();

    // Funci�n que analiza una expresi�n.
    shared_ptr<ASTNode> parseExpression();

    // Funci�n que analiza una expresi�n primaria.
    shared_ptr<ASTNode> parsePrimary();

    // Funci�n que analiza una operaci�n binaria.
    shared_ptr<ASTNode> parseBinaryOp(int precedence, shared_ptr<ASTNode> left);

    // Funci�n que verifica si hemos llegado al final de los tokens.
    bool isAtEnd() const;

    // Funci�n que obtiene el token actual.
    Token advance();

    // Funci�n que obtiene el token actual sin avanzar.
    Token peek() const;

    // Funci�n que obtiene el siguiente token sin avanzar.
    Token peekNext() const;

    // Funci�n que consume un token esperado.
    Token consume(TokenType type, const string& message);

    // Funci�n que verifica si el token actual es del tipo esperado.
    bool check(TokenType type) const;

    // Funci�n que verifica si el token actual es del tipo esperado y avanza.
    bool match(TokenType type);
};

#endif

