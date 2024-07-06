#include "Lexer.h"
#include <cctype>

// Constructor que inicializa el lexer con el c�digo fuente.
Lexer::Lexer(const string& source) : source(source), current(0) {}

// Funci�n para tokenizar todo el c�digo fuente.
// Devuelve un vector de objetos Token que representan los tokens en el c�digo fuente.
vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        tokens.push_back(lexToken());
    }
    return tokens;
}

// Avanza la posici�n actual y devuelve el car�cter actual.
char Lexer::advance() {
    return source[current++];
}

// Mira el car�cter actual sin avanzar la posici�n.
char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

// Verifica si el lexer ha llegado al final del c�digo fuente.
bool Lexer::isAtEnd() const {
    return current >= source.size();
}

// Omite los caracteres de espacio en blanco en el c�digo fuente.
void Lexer::skipWhitespace() {
    while (!isAtEnd() && isspace(peek())) {
        advance();
    }
}

// Lexea un solo token del c�digo fuente.
// Devuelve un objeto Token que representa el token lexeado.
Token Lexer::lexToken() {
    char currentChar = advance();
    if (isalpha(currentChar)) {
        return lexIdentifier();
    } else if (isdigit(currentChar)) {
        return lexNumber();
    } else {
        return lexOperator();
    }
}

// Lexea un token identificador del c�digo fuente.
// Devuelve un objeto Token que representa el identificador.
Token Lexer::lexIdentifier() {
    string value(1, source[current - 1]);
    while (!isAtEnd() && isalnum(peek())) {
        value += advance();
    }
    return Token(TokenType::IDENTIFIER, value);
}

// Lexea un token de n�mero del c�digo fuente.
// Devuelve un objeto Token que representa el n�mero.
Token Lexer::lexNumber() {
    string value(1, source[current - 1]);
    while (!isAtEnd() && isdigit(peek())) {
        value += advance();
    }
    return Token(TokenType::NUMBER, value);
}

// Lexea un token de operador del c�digo fuente.
// Devuelve un objeto Token que representa el operador.
Token Lexer::lexOperator() {
    char currentChar = source[current - 1];
    switch (currentChar) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '>':
        case '<':
        case '(':
        case ')':
            return Token(TokenType::OPERATOR, string(1, currentChar));
        default:
            return Token(TokenType::UNKNOWN, string(1, currentChar));
    }
}

