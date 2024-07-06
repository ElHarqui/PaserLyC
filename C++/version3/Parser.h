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
    // Constructor que inicializa el parser con una lista de tokens.
    Parser(const vector<Token>& tokens);

    // Funci�n para parsear todos los tokens en un AST.
    // Devuelve un puntero compartido al nodo ra�z del AST.
    shared_ptr<ASTNode> parse();

private:
    vector<Token> tokens; // La lista de tokens a parsear.
    size_t current; // La posici�n actual en la lista de tokens.

    // Funci�n para avanzar al siguiente token.
    Token advance();

    // Funci�n para obtener el token actual sin avanzar la posici�n.
    Token peek() const;

    // Funci�n para verificar si el parser ha llegado al final de los tokens.
    bool isAtEnd() const;

    // Funci�n para parsear una declaraci�n.
    shared_ptr<ASTNode> parseStatement();

    // Funci�n para parsear una expresi�n.
    shared_ptr<ASTNode> parseExpression();

    // Funci�n para parsear un t�rmino (parte de una expresi�n).
    shared_ptr<ASTNode> parseTerm();

    // Funci�n para parsear un factor (parte de un t�rmino).
    shared_ptr<ASTNode> parseFactor();
};

#endif

