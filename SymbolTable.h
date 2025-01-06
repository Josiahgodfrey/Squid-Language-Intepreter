#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class SymbolTable {
private:
    std::unordered_map<std::string, int> variables;
    std::unordered_map<std::string, Function> functions;

public:
    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }

    int getVariable(const std::string& name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        } else {
            std::cerr << "Error: Variable " << name << " not found." << std::endl;
            exit(1);
        }
    }

    void setFunction(const std::string& name, const Function& function) {
        functions[name] = function;
    }

    Function getFunction(const std::string& name) {
        if (functions.find(name) != functions.end()) {
            return functions[name];
        } else {
            std::cerr << "Error: Function " << name << " not found." << std::endl;
            exit(1);
        }
    }
};

// Add support for nested scopes
class Scope {
private:
    std::unordered_map<std::string, int> variables;

public:
    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }

    int getVariable(const std::string& name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        } else {
            std::cerr << "Error: Variable " << name << " not found in scope." << std::endl;
            exit(1);
        }
    }
};

#endif // SYMBOLTABLE_H
