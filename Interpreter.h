#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"
#include "NodeType.h"
#include "SymbolTable.h"
#include "Token.h"
#include "Function.h"

class Interpreter {
private:
    Lexer lexer;
    Parser parser;
    SymbolTable symbolTable;

public:
     Interpreter(std::string input) : lexer(input), parser(lexer), symbolTable() {};

    void evaluateAST(Node* node) {
        if (!node) return; // Check for null node

        switch (node->type) {
            case NodeType::Expression:
                std::cout << "Result: " << evaluateExpression(node) << std::endl;
                break;
            case NodeType::Statement:
                evaluateStatement(node);
                break;
            case NodeType::FunctionCall:
                evaluateFunctionCall(node);
                break;
            case NodeType::IfStatement:
                evaluateIfStatement(node);
                break;
            case NodeType::WhileLoop:
                evaluateWhileLoop(node);
                break;
            default:
                // Handle other node types as needed
                break;
        }
    }

    int evaluateExpression(Node* node) {
        if (!node) return 0; // Check for null node

        switch (node->type) {
            case NodeType::Addition:
                return evaluateExpression(node->left) + evaluateExpression(node->right);
            case NodeType::Subtraction:
                return evaluateExpression(node->left) - evaluateExpression(node->right);
            default:
                // Handle other expression types as needed
                return 0;
        }
    }

    void evaluateStatement(Node* node) {
        if (!node) return; // Check for null node

        if (node->type == NodeType::Assignment) {
            std::string variableName = node->left->value;
            int value = evaluateExpression(node->right);
            symbolTable.setVariable(variableName, value);
        }
    }

    void evaluateFunctionCall(Node* node) {
        if (!node) return; // Check for null node

        std::string functionName = node->value;
        std::vector<Node*> arguments = node->arguments;

        Function function = symbolTable.getFunction(functionName);
        std::vector<int> argumentValues;

        for (Node* argument : arguments) {
            argumentValues.push_back(evaluateExpression(argument));
        }

        std::cout << "Result: " << function.call(argumentValues) << std::endl;
    }

    void evaluateIfStatement(Node* node) {
        if (!node) return; // Check for null node

        if (evaluateExpression(node->condition) != 0) {
            evaluateAST(node->trueBranch);
        } else {
            evaluateAST(node->falseBranch);
        }
    }

    void evaluateWhileLoop(Node* node) {
        if (!node) return; // Check for null node

        while (evaluateExpression(node->condition) != 0) {
            evaluateAST(node->body);
        }
    }
};

#endif
