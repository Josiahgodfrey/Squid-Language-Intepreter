#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>

// Define the Function class
class Function {
public:
    std::string name;
    std::vector<std::string> parameters;
    std::vector<Token> body;

    Function(std::string n, std::vector<std::string> p, std::vector<Token> b)
        : name(n), parameters(p), body(b) {}
};
class SymbolTable {
private:
    std::unordered_map<std::string, int> variables;
    std::unordered_map<std::string, Function> functions;

public:
    void setVariable(std::string name, int value) {
        variables[name] = value;
    }

    int getVariable(std::string name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        } else {
            std::cerr << "Error: Variable " << name << " not found in symbol table." << std::endl;
            exit(1);
        }
    }

    void addFunction(Function function) {
        functions[function.name] = function;
    }

    Function getFunction(std::string name) {
        if (functions.find(name) != functions.end()) {
            return functions[name];
        } else {
            std::cerr << "Error: Function " << name << " not found in symbol table." << std::endl;
            exit(1);
        }
    }

    // Add support for nested scopes
    class Scope {
    private:
        std::unordered_map<std::string, int> variables;

    public:
        void setVariable(std::string name, int value) {
            variables[name] = value;
        }

        int getVariable(std::string name) {
            if (variables.find(name) != variables.end()) {
                return variables[name];
            } else {
                std::cerr << "Error: Variable " << name << " not found in scope." << std::endl;
                exit(1);
            }
        }
    };
};

#endif