#ifndef PARSER_H
#define PARSER_H

#include "Function.h"
#include "Lexer.h"
#include <unordered_map>
#include <vector>
#include <string> // Added for std::string
#include "Node.h"
#include "Token.h"


class Lexer;
struct Token {
    TokenType type;
    std::string text;

    Token() = default; // Default constructor
    Token(TokenType type, std::string text) : type(type), text(text) {}
};

class Parser {
private:
    Lexer lexer;
    Token currentToken;
    Function* currentFunction;

    void eat(TokenType type);
    bool parseCondition(); // Added declaration for parseCondition
    void parseBlock(); // Added declaration for parseBlock
    int factor();
    int term();
    int expr();

public:
    Parser(Lexer lexer) : lexer(lexer) {
        currentToken = lexer.getNextToken();
    }

    void parse(std::vector<Token>& tokens);
    void parseFunction();
    void parseIfStatement();
    void parseWhileStatement();
};

class Function {
public:
    std::string name;
    std::vector<std::string> parameters; // Fixed vector declaration
    std::vector<Token> body;

    Function(std::string name, std::vector<std::string> parameters, std::vector<Token> body)
        : name(name), parameters(parameters), body(body) {}
};

void Parser::parseFunction() {
    eat(FUNCTION);
    std::string name = currentToken.text;
    eat(IDENTIFIER);

    eat(LPAREN);
    std::vector<std::string> parameters;
    while (currentToken.type != RPAREN) {
        std::string parameter = currentToken.text;
        eat(IDENTIFIER);
        parameters.push_back(parameter);

        if (currentToken.type == COMMA) {
            eat(COMMA);
        }
    }
    eat(RPAREN);

    eat(LBRACE);
    std::vector<Token> body;
    while (currentToken.type != RBRACE) {
        body.push_back(currentToken);
        currentToken = lexer.getNextToken();
    }
    eat(RBRACE);

    currentFunction = new Function(name, parameters, body);
}

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
