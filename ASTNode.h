#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <memory>
#include <vector>

using namespace std;

// Enum para los tipos de nodos que nuestro AST reconocerá.
enum class ASTNodeType {
    NUMBER,
    VARIABLE,
    BINARY_OP
};

// Clase ASTNode que representa un nodo en nuestro árbol de sintaxis abstracta.
class ASTNode {
public:
    ASTNodeType type; // El tipo del nodo.
    string value; // El valor del nodo.
    shared_ptr<ASTNode> left; // El nodo hijo izquierdo.
    shared_ptr<ASTNode> right; // El nodo hijo derecho.

    // Constructor para inicializar un nodo sin hijos.
    ASTNode(ASTNodeType type, const string& value) 
        : type(type), value(value), left(nullptr), right(nullptr) {}

    // Constructor para inicializar un nodo con hijos.
    ASTNode(ASTNodeType type, const string& value, 
            shared_ptr<ASTNode> left, shared_ptr<ASTNode> right) 
        : type(type), value(value), left(left), right(right) {}
};

#endif

