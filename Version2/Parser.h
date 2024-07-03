#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "Token.h"
#include "SymbolTable.h"

using namespace std;

class Parser {
public:
    Parser(const vector<Token>& tokens, SymbolTable& symTable);
    void parse();

private:
    vector<Token> tokens;
    size_t pos;
    SymbolTable& symTable;

    void parseReturnStatement();
    void parseAssignment();
    void parseExpression();
    void parseTerm();
    void parseFactor();
};

#endif // PARSER_H

