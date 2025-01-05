#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

class Interpreter {
private:
    Lexer lexer;
    Parser parser;
    SymbolTable symbolTable;

public:
    Interpreter(std::string input) : lexer(input), parser(lexer), symbolTable() {}

    void interpret();
};

#endif