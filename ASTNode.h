#ifndef ASTNODE_H
#define ASTNODE_H

#include <memory>
#include <vector>
#include <string>

enum class ASTNodeType {
    PROGRAM, STATEMENT, EXPRESSION, VARIABLE_DECLARATION, ASSIGNMENT, BINARY_OP, IDENTIFIER, NUMBER
};

class ASTNode {
public:
    ASTNodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(ASTNodeType type, const std::string& value) : type(type), value(value) {}
    void addChild(std::shared_ptr<ASTNode> child) {
        children.push_back(child);
    }
};

#endif

