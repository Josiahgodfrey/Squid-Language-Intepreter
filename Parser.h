#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include <unordered_map>

class Parser {
private:
    Lexer lexer;
    Token currentToken;

    void eat(TokenType type);
    int factor();
    int term();
    int expr();

public:
    Parser(Lexer lexer) : lexer(lexer) {
        currentToken = lexer.getNextToken();
    }

    void parse();
};

#endif