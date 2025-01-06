#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <iostream>
#include <string>
#include <vector>
#include "TokenType.h"

using namespace std;

enum class TokenType {
    NUMBER,
    VARIABLE,
    ASSIGN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    PRINT,
    END,
    POWER,
    AND,
    OR,
    NOT,
};


class Lexer {
private:
    string input;
    int position;

public:
    Lexer(string input) : input(input), position(0) {}
    vector<Token> Lexer::tokenize();
    Token Lexer::getNextToken();
};

#endif