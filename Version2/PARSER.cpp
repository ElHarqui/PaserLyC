#include "Parser.h"
#include <iostream>

Parser::Parser(const vector<Token>& tokens, SymbolTable& symTable) 
    : tokens(tokens), pos(0), symTable(symTable) {}

void Parser::parse() {
    while (pos < tokens.size() && tokens[pos].type != TokenType::END) {
        if (tokens[pos].type == TokenType::KEYWORD && tokens[pos].value == "return") {
            parseReturnStatement();
        } else if (tokens[pos].type == TokenType::IDENTIFIER) {
            parseAssignment();
        } else {
            parseExpression();
        }
    }
}

void Parser::parseReturnStatement() {
    ++pos;  // Consumir 'return'
    parseExpression();
    if (pos < tokens.size() && tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == ";") {
        ++pos;  // Consumir ';'
    } else {
        cerr << "Error: Expected ';' after return statement" << endl;
    }
}

void Parser::parseAssignment() {
    string varName = tokens[pos].value;
    ++pos;  // Consumir el identificador
    if (pos < tokens.size() && tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == "=") {
        ++pos;  // Consumir '='
        parseExpression();
        symTable.addSymbol(varName, "int"); // Añadir símbolo a la tabla con tipo 'int'
        if (pos < tokens.size() && tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == ";") {
            ++pos;  // Consumir ';'
        } else {
            cerr << "Error: Expected ';' after assignment" << endl;
        }
    } else {
        cerr << "Error: Expected '=' in assignment" << endl;
    }
}

void Parser::parseExpression() {
    parseTerm();
    while (pos < tokens.size() && (tokens[pos].value == "+" || tokens[pos].value == "-")) {
        ++pos; // Consumir '+' o '-'
        parseTerm();
    }
}

void Parser::parseTerm() {
    parseFactor();
    while (pos < tokens.size() && (tokens[pos].value == "*" || tokens[pos].value == "/")) {
        ++pos; // Consumir '*' o '/'
        parseFactor();
    }
}

void Parser::parseFactor() {
    if (tokens[pos].type == TokenType::NUMBER || tokens[pos].type == TokenType::IDENTIFIER) {
        ++pos; // Consumir número o identificador
    } else if (tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == "(") {
        ++pos; // Consumir '('
        parseExpression();
        if (pos < tokens.size() && tokens[pos].type == TokenType::OPERATOR && tokens[pos].value == ")") {
            ++pos; // Consumir ')'
        } else {
            cerr << "Error: Expected ')'" << endl;
        }
    } else if (tokens[pos].type == TokenType::OPERATOR && (tokens[pos].value == ">" || tokens[pos].value == "<" || tokens[pos].value == ">=" || tokens[pos].value == "<=")) {
        ++pos; // Consumir '>', '<', '>=', '<='
    } else {
        cerr << "Error: Expected expression" << endl;
        ++pos; // Asegurarse de que avanzamos para evitar bucles infinitos
    }
}

