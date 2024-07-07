#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

// La clase Lexer es responsable de convertir el c�digo fuente en una serie de tokens.
class Lexer {
public:
    // Constructor que inicializa el lexer con el c�digo fuente.
    Lexer(const string& source);

    // Funci�n para tokenizar todo el c�digo fuente.
    // Devuelve un vector de objetos Token que representan los tokens en el c�digo fuente.
    vector<Token> tokenize();

private:
    string source; // El c�digo fuente a tokenizar.
    size_t current; // La posici�n actual en el c�digo fuente.

    // Avanza la posici�n actual y devuelve el car�cter actual.
    char advance();

    // Mira el car�cter actual sin avanzar la posici�n.
    char peek() const;

    // Verifica si el lexer ha llegado al final del c�digo fuente.
    bool isAtEnd() const;

    // Omite los caracteres de espacio en blanco en el c�digo fuente.
    void skipWhitespace();

    // Lexea un solo token del c�digo fuente.
    // Devuelve un objeto Token que representa el token lexeado.
    Token lexToken();

    // Lexea un token identificador del c�digo fuente.
    // Devuelve un objeto Token que representa el identificador.
    Token lexIdentifier();

    // Lexea un token de n�mero del c�digo fuente.
    // Devuelve un objeto Token que representa el n�mero.
    Token lexNumber();

    // Lexea un token de operador del c�digo fuente.
    // Devuelve un objeto Token que representa el operador.
    Token lexOperator();
};

#endif

