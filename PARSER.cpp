#include "Parser.h"
#include <stdexcept>

using namespace std;

shared_ptr<ASTNode> Parser::parse() {
    return parseDeclaration();
}

shared_ptr<ASTNode> Parser::parseDeclaration() {
    if (match(TokenType::KEYWORD)) {
        string type = tokens[current - 1].value;
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
        consume(TokenType::DELIMITER, "Expected ';' after declaration.");
        return make_shared<ASTNode>(ASTNodeType::VARIABLE, name.value);
    }
    return parseExpression();
}

shared_ptr<ASTNode> Parser::parseExpression() {
    shared_ptr<ASTNode> left = parsePrimary();
    return parseBinaryOp(0, left);
}

shared_ptr<ASTNode> Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
        return make_shared<ASTNode>(ASTNodeType::NUMBER, tokens[current - 1].value);
    }
    if (match(TokenType::IDENTIFIER)) {
        return make_shared<ASTNode>(ASTNodeType::VARIABLE, tokens[current - 1].value);
    }
    throw runtime_error("Error: Expected expression");
}

shared_ptr<ASTNode> Parser::parseBinaryOp(int precedence, shared_ptr<ASTNode> left) {
    while (true) {
        if (match(TokenType::OPERATOR)) {
            string op = tokens[current - 1].value;
            shared_ptr<ASTNode> right = parsePrimary();
            left = make_shared<ASTNode>(ASTNodeType::BINARY_OP, op, left, right);
        } else {
            break;
        }
    }
    return left;
}

bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::END_OF_FILE;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::peekNext() const {
    if (isAtEnd()) return tokens[current];
    return tokens[current + 1];
}

Token Parser::consume(TokenType type, const string& message) {
    if (check(type)) return advance();
    throw runtime_error(message);
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return tokens[current].type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

