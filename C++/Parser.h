#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

enum class ASTNodeType {
    ASSIGNMENT,
    EXPRESSION,
    TERM,
    FACTOR
};

class ASTNode {
public:
    ASTNodeType type;
    string value;
    vector<shared_ptr<ASTNode>> children;

    ASTNode(ASTNodeType type, const string& value) : type(type), value(value) {}
};

class Parser {
public:
    Parser(const vector<Token>& tokens);
    shared_ptr<ASTNode> parse();

private:
    vector<Token> tokens;
    size_t currentIndex;

    Token advance();
    Token peek();
    bool isAtEnd();

    shared_ptr<ASTNode> parseStatement();
    shared_ptr<ASTNode> parseExpression();
    shared_ptr<ASTNode> parseTerm();
    shared_ptr<ASTNode> parseFactor();
};

#endif // PARSER_H

