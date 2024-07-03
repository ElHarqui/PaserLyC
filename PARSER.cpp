#include "Parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

std::shared_ptr<ASTNode> Parser::parse() {
    auto root = std::make_shared<ASTNode>(ASTNodeType::PROGRAM, "program");
    while (!isAtEnd()) {
        root->addChild(parseStatement());
    }
    return root;
}

std::shared_ptr<ASTNode> Parser::parseStatement() {
    if (match(TokenType::KEYWORD)) {
        auto type = advance();
        auto identifier = advance();
        if (match(TokenType::OPERATOR, ";")) {
            advance();
            return std::make_shared<ASTNode>(ASTNodeType::VARIABLE_DECLARATION, identifier.value);
        }
    } else if (match(TokenType::IDENTIFIER)) {
        auto identifier = advance();
        if (match(TokenType::OPERATOR, "=")) {
            advance();
            auto expr = parseExpression();
            if (match(TokenType::OPERATOR, ";")) {
                advance();
                auto node = std::make_shared<ASTNode>(ASTNodeType::ASSIGNMENT, identifier.value);
                node->addChild(expr);
                return node;
            }
        }
    }
    std::cerr << "Error: Expected statement" << std::endl;
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseExpression() {
    auto left = parsePrimary();
    while (match(TokenType::OPERATOR, "+") || match(TokenType::OPERATOR, "-") ||
           match(TokenType::OPERATOR, "*") || match(TokenType::OPERATOR, "/")) {
        Token op = advance();
        auto right = parsePrimary();
        auto node = std::make_shared<ASTNode>(ASTNodeType::BINARY_OP, op.value);
        node->addChild(left);
        node->addChild(right);
        left = node;
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<ASTNode>(ASTNodeType::NUMBER, advance().value);
    } else if (match(TokenType::IDENTIFIER)) {
        return std::make_shared<ASTNode>(ASTNodeType::IDENTIFIER, advance().value);
    }
    std::cerr << "Error: Expected primary expression" << std::endl;
    return nullptr;
}

Token Parser::advance() {
    return tokens[pos++];
}

Token Parser::peek() const {
    return tokens[pos];
}

bool Parser::match(TokenType type, const std::string& value) {
    return !isAtEnd() && peek().type == type && (value.empty() || peek().value == value);
}

bool Parser::isAtEnd() const {
    return pos >= tokens.size();
}

