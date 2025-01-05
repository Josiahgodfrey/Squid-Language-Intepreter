#include "Lexer.h"
#include "Parser.h"
#include "Node.h"
#include "NodeType.h"
#include "SymbolTable.h"
#include <vector>
#include <string>
#include <iostream>

class Interpreter {
private:
    Lexer lexer;
    Parser parser;
    SymbolTable symbolTable;

public:
    Interpreter(std::string input) : lexer(input), parser(lexer), symbolTable() {}

    void interpret() {
        // Tokenize the input
        std::vector<Token> tokens = lexer.tokenize();

        // Parse the tokens
        Node* ast = parser.parse(tokens);

        // Evaluate the abstract syntax tree (AST) and execute the program
        evaluateAST(ast);
    }

    void evaluateAST(Node* node) {
        // Implement the logic to evaluate the abstract syntax tree (AST) and execute the program

        // Example: Evaluate the AST recursively and perform the necessary operations
        if (node->type == NodeType::Expression) {
            // Evaluate the expression
            int result = evaluateExpression(node);

            // Perform the necessary operations with the result
            std::cout << "Result: " << result << std::endl;
        } else if (node->type == NodeType::Statement) {
            // Evaluate the statement
            evaluateStatement(node);
        } else if (node->type == NodeType::FunctionCall) {
            // Evaluate the function call
            evaluateFunctionCall(node);
        } else if (node->type == NodeType::IfStatement) {
            // Evaluate the if-statement
            evaluateIfStatement(node);
        } else if (node->type == NodeType::WhileLoop) {
            // Evaluate the while loop
            evaluateWhileLoop(node);
        } else {
            // Handle other node types as needed
        }
    }

    int evaluateExpression(Node* node) {
        // Implement the logic to evaluate expressions and return the result

        // Example: Evaluate the expression recursively and return the result
        if (node->type == NodeType::Addition) {
            int left = evaluateExpression(node->left);
            int right = evaluateExpression(node->right);
            return left + right;
        } else if (node->type == NodeType::Subtraction) {
            int left = evaluateExpression(node->left);
            int right = evaluateExpression(node->right);
            return left - right;
        } else {
            // Handle other expression types as needed
            return 0;
        }
    }

    void evaluateStatement(Node* node) {
        // Implement the logic to evaluate statements

        // Example: Evaluate the statement and perform the necessary operations
        if (node->type == NodeType::Assignment) {
            std::string variableName = node->left->value;
            int value = evaluateExpression(node->right);
            symbolTable.setVariable(variableName, value);
        } else {
            // Handle other statement types as needed
        }
    }

    void evaluateFunctionCall(Node* node) {
        // Implement the logic to evaluate function calls

        // Example: Evaluate the function call and perform the necessary operations
        std::string functionName = node->value;
        std::vector<Node*> arguments = node->arguments;

        // Lookup the function in the symbol table
        Function function = symbolTable.getFunction(functionName);

        // Evaluate the arguments
        std::vector<int> argumentValues;
        for (Node* argument : arguments) {
            int value = evaluateExpression(argument);
            argumentValues.push_back(value);
        }

        // Call the function with the evaluated arguments
        int result = function.call(argumentValues);

        // Perform the necessary operations with the result
        std::cout << "Result: " << result << std::endl;
    }

    void evaluateIfStatement(Node* node) {
        // Implement the logic to evaluate if-statements

        // Example: Evaluate the if-statement and perform the necessary operations
        int condition = evaluateExpression(node->condition);

        if (condition != 0) {
            // Evaluate the true branch
            evaluateAST(node->trueBranch);
        } else {
            // Evaluate the false branch
            evaluateAST(node->falseBranch);
        }
    }

    void evaluateWhileLoop(Node* node) {
        // Implement the logic to evaluate while loops

        // Example: Evaluate the while loop and perform the necessary operations
        while (evaluateExpression(node->condition) != 0) {
            // Evaluate the body of the while loop
            evaluateAST(node->body);
        }
    }
};