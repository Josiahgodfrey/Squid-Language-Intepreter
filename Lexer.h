#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>

using namespace std;

enum TokenType {
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


struct Token {
    TokenType type;
    string text;

    Token(TokenType type, string text) : type(type), text(text) {}
};

class Lexer {
    private:
        string input;
        int position;

    public:
        Lexer(string input) : input(input), position(0) {}

        Token getNextToken() {
            //implementing the logic to tokenize the input string
            //return the next token based on the grammer rules
        }
};

#endif