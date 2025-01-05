#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

enum class NodeType {
    Expression,
    Statement,
    FunctionCall,
    IfStatement,
    WhileLoop,
    // Add other node types as needed
};

struct Node {
    NodeType type;
    std::string value;
    Node* left;
    Node* right;
    std::vector<Node*> arguments;
    Node* trueBranch;
    Node* falseBranch;
    Node* condition;
    Node* body;

    Node(NodeType type, std::string value = "")
        : type(type), value(value), left(nullptr), right(nullptr), arguments(), trueBranch(nullptr), falseBranch(nullptr), condition(nullptr), body(nullptr) {}

    ~Node() {
        delete left;
        delete right;
        for (Node* argument : arguments) {
            delete argument;
        }
        delete trueBranch;
        delete falseBranch;
        delete condition;
        delete body;
    }
};

#endif // NODE_H