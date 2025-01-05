#include "SymbolTable.h"

void SymbolTable::setVariable(std::string name, int value) {
    // Check if the variable already exists in the symbol table
    if (variables.find(name) != variables.end()) {
        std::cerr << "Warning: Variable " << name << " already exists in the symbol table. Overwriting value." << std::endl;
    }

    // Set the value of the variable in the symbol table
    variables[name] = value;
}

int SymbolTable::getVariable(std::string name) {
    // Check if the variable exists in the symbol table
    if (variables.find(name) == variables.end()) {
        std::cerr << "Error: Variable " << name << " not found in the symbol table." << std::endl;
        exit(1);
    }

    // Return the value of the variable from the symbol table
    return variables[name];
}

void SymbolTable::addFunction(Function function) {
    // Check if the function already exists in the symbol table
    if (functions.find(function.name) != functions.end()) {
        std::cerr << "Warning: Function " << function.name << " already exists in the symbol table. Overwriting function." << std::endl;
    }

    // Add the function to the symbol table
    functions[function.name] = function;
}

Function SymbolTable::getFunction(std::string name) {
    // Check if the function exists in the symbol table
    if (functions.find(name) == functions.end()) {
        std::cerr << "Error: Function " << name << " not found in the symbol table." << std::endl;
        exit(1);
    }

    // Return the function from the symbol table
    return functions[name];
}