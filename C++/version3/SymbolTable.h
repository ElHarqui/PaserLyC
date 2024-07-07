#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
using namespace std;

class SymbolTable {
public:
    void addSymbol(const string& name, const string& type);
    string lookup(const string& name);

private:
    unordered_map<string, string> symbols;
};

#endif // SYMBOLTABLE_H

