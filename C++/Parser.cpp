#include "Parser.h"

Parser::Parser(const vector<Token>& tokens) : tokens(tokens), currentIndex(0) {}

shared_ptr<ASTNode> Parser::parse() {
    return parseStatement();
}

Token Parser::advance() {
    if (!isAtEnd()) currentIndex++;
    return tokens[currentIndex];
}

Token Parser::peek() {
    if (isAtEnd()) return Token(TokenType::UNKNOWN, "");
    return tokens[currentIndex];
}

bool Parser::isAtEnd() {
    return currentIndex >= tokens.size();
}

shared_ptr<ASTNode> Parser::parseStatement() {
    auto node = make_shared<ASTNode>(ASTNodeType::ASSIGNMENT, "");
    node->children.push_back(parseExpression());
    if (peek().type == TokenType::SEPARATOR) {
        advance();
    } else {
        throw runtime_error("Expected ';' after expression");
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseExpression() {
    auto node = make_shared<ASTNode>(ASTNodeType::EXPRESSION, "");
    node->children.push_back(parseTerm());
    while (peek().type == TokenType::OPERATOR && (peek().value == "+" || peek().value == "-")) {
        auto opNode = make_shared<ASTNode>(ASTNodeType::EXPRESSION, advance().value);
        opNode->children.push_back(node);
        opNode->children.push_back(parseTerm());
        node = opNode;
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseTerm() {
    auto node = make_shared<ASTNode>(ASTNodeType::TERM, "");
    node->children.push_back(parseFactor());
    while (peek().type == TokenType::OPERATOR && (peek().value == "*" || peek().value == "/")) {
        auto opNode = make_shared<ASTNode>(ASTNodeType::TERM, advance().value);
        opNode->children.push_back(node);
        opNode->children.push_back(parseFactor());
        node = opNode;
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseFactor() {
    auto token = advance();
    if (token.type == TokenType::IDENTIFIER || token.type == TokenType::NUMBER) {
        return make_shared<ASTNode>(ASTNodeType::FACTOR, token.value);
    } else if (token.value == "(") {
        auto node = parseExpression();
        if (advance().value != ")") {
            throw runtime_error("Expected ')'");
        }
        return node;
    } else {
        throw runtime_error("Unexpected token: " + token.value);
    }
}

