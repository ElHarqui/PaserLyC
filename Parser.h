#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <string>
#include "Token.h"
#include "ASTNode.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parsePrimary();

    Token advance();
    Token peek() const;
    bool match(TokenType type, const std::string& value = "");
    bool isAtEnd() const;
};

#endif

