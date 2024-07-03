#include "Parser.h"

// Constructor que inicializa el parser con una lista de tokens.
Parser::Parser(const vector<Token>& tokens) : tokens(tokens), current(0) {}

// Función para parsear todos los tokens en un AST.
// Devuelve un puntero compartido al nodo raíz del AST.
shared_ptr<ASTNode> Parser::parse() {
    return parseStatement();
}

// Función para avanzar al siguiente token.
Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

// Función para obtener el token actual sin avanzar la posición.
Token Parser::peek() const {
    if (isAtEnd()) return Token(TokenType::UNKNOWN, "");
    return tokens[current];
}

// Función para verificar si el parser ha llegado al final de los tokens.
bool Parser::isAtEnd() const {
    return current >= tokens.size();
}

// Función para parsear una declaración.
shared_ptr<ASTNode> Parser::parseStatement() {
    shared_ptr<ASTNode> expr = parseExpression();
    if (peek().type != TokenType::OPERATOR || peek().value != ";") {
        throw runtime_error("Error: Expected ';' after expression");
    }
    advance(); // Consume el ';'
    return expr;
}

// Función para parsear una expresión.
shared_ptr<ASTNode> Parser::parseExpression() {
    shared_ptr<ASTNode> left = parseTerm();
    while (peek().type == TokenType::OPERATOR && (peek().value == "+" || peek().value == "-")) {
        Token op = advance();
        shared_ptr<ASTNode> right = parseTerm();
        left = make_shared<ASTNode>(ASTNodeType::BINARY_OP, op.value, left, right);
    }
    return left;
}

// Función para parsear un término (parte de una expresión).
shared_ptr<ASTNode> Parser::parseTerm() {
    shared_ptr<ASTNode> left = parseFactor();
    while (peek().type == TokenType::OPERATOR && (peek().value == "*" || peek().value == "/")) {
        Token op = advance();
        shared_ptr<ASTNode> right = parseFactor();
        left = make_shared<ASTNode>(ASTNodeType::BINARY_OP, op.value, left, right);
    }
    return left;
}

// Función para parsear un factor (parte de un término).
shared_ptr<ASTNode> Parser::parseFactor() {
    Token token = advance();
    if (token.type == TokenType::NUMBER) {
        return make_shared<ASTNode>(ASTNodeType::NUMBER, token.value);
    } else if (token.type == TokenType::IDENTIFIER) {
        return make_shared<ASTNode>(ASTNodeType::VARIABLE, token.value);
    } else if (token.type == TokenType::OPERATOR && token.value == "(") {
        shared_ptr<ASTNode> expr = parseExpression();
        if (peek().type != TokenType::OPERATOR || peek().value != ")") {
            throw runtime_error("Error: Expected ')'");
        }
        advance(); // Consume el ')'
        return expr;
    } else {
        throw runtime_error("Error: Unexpected token");
    }
}

