#include "SymbolTable.h"

void SymbolTable::addSymbol(const string& name, const string& type) {
    symbols[name] = type;
}

string SymbolTable::lookup(const string& name) {
    if (symbols.find(name) != symbols.end()) {
        return symbols[name];
    }
    return "";
}

