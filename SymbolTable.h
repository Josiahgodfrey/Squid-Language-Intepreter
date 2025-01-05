#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, int> variables;

public:
    void setVariable(std::string name, int value);
    int getVariable(std::string name);
};

#endif