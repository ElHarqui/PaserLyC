#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

using namespace std;

// La clase SymbolTable es responsable de mantener un registro de las variables y sus tipos.
class SymbolTable {
public:
    // Función para agregar una nueva variable a la tabla de símbolos.
    void add(const string& name, const string& type) {
        table[name] = type;
    }

    // Función para verificar si una variable está en la tabla de símbolos.
    bool exists(const string& name) const {
        return table.find(name) != table.end();
    }

    // Función para obtener el tipo de una variable.
    string getType(const string& name) const {
        auto it = table.find(name);
        if (it != table.end()) {
            return it->second;
        }
        return "";
    }

private:
    unordered_map<string, string> table; // La tabla de símbolos.
};

#endif

