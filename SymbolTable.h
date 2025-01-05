#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, int> variables;
    std::unordered_map<std::string, Function> functions;

public:
    void setVariable(std::string name, int value);
    int getVariable(std::string name);

    void addVvariable(std::string name, int value) {
        variables[name] = value;
    }

    int getVvariable(std::string name) {
        if (variables.find(name) == variables.end()) {
            return variables[name];
        }
        else {
            std::cerr << "Error: Variable " << name << " not found in symbol table." << std::endl;
            exit(1);
        }
    }

//function handling logic
    void addFunction(Function function) {
        functions[function.name] = function;
    }

    Function getFunction(std::string name) {
        if (functions.find(name) != functions.end()) {
            return functions[name];
        }
        else {
            std::cerr << "Function not found: " << name << std::endl;
            exit(1);
        }
    }
};

#endif