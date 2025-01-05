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

// Add a Function class to represent functions
class Function {
public:
    std::string name;
    std::vector<std::string> parameters;
    std::vector<Token> body;

    Function(std::string name, std::vector<std::string> parameters, std::vector<Token> body)
        : name(name), parameters(parameters), body(body) {}
};


// Modifying the Parser class to handle if statements
void Parser::parseIfStatement() {
    eat(IF);
    eat(LPAREN);
    bool condition = parseCondition();
    eat(RPAREN);

    if (condition) {
        parseBlock();
    }
    else if (currentToken.type == ELSE) {
        eat(ELSE);
        parseBlock();
    }
}

// Modify the Parser class to handle while statements
void Parser::parseWhileStatement() {
    eat(WHILE);
    eat(LPAREN);
    bool condition = parseCondition();
    eat(RPAREN);

    while (condition) {
        parseBlock();
        condition = parseCondition();
    }
}



#endif