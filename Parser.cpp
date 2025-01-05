#include "Parser.h"

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = lexer.getNextToken();
    } else {
        std::cerr << "Unexpected token: " << currentToken.text << std::endl;
        exit(1);
    }
}

// Function to parse and execute statements
void Parser::parseStatement() {
    if (currentToken.type == VARIABLE) {
        parseVariableDeclaration();
    } else if (currentToken.type == IF) {
        parseIfStatement();
    } else if (currentToken.type == WHILE) {
        parseWhileStatement();
    } else if (currentToken.type == FUNCTION) {
        parseFunctionDeclaration();
    } else {
        parseExpression();
    }
}

// Function to parse and execute variable declarations
void Parser::parseVariableDeclaration() {
    eat(VARIABLE);
    std::string name = currentToken.text;
    eat(ASSIGN);
    int value = parseExpression();
    symbolTable.addVariable(name, value);
}

// Function to parse and execute if statements
void Parser::parseIfStatement() {
    eat(IF);
    eat(LPAREN);
    bool condition = parseExpression();
    eat(RPAREN);
    if (condition) {
        parseBlock();
    } else if (currentToken.type == ELSE) {
        eat(ELSE);
        parseBlock();
    }
}

// Function to parse and execute while statements
void Parser::parseWhileStatement() {
    eat(WHILE);
    eat(LPAREN);
    bool condition = parseExpression();
    eat(RPAREN);
    while (condition) {
        parseBlock();
        condition = parseExpression();
    }
}

// Function to parse and execute function declarations
void Parser::parseFunctionDeclaration() {
    eat(FUNCTION);
    std::string name = currentToken.text;
    eat(LPAREN);
    std::vector<std::string> parameters = parseParameterList();
    eat(RPAREN);
    eat(BLOCK_START);
    std::vector<Token> body = parseBlock();
    eat(BLOCK_END);
    symbolTable.addFunction(name, parameters, body);
}

// Function to parse a parameter list
std::vector<std::string> Parser::parseParameterList() {
    std::vector<std::string> parameters;
    if (currentToken.type != RPAREN) {
        parameters.push_back(currentToken.text);
        eat(VARIABLE);
        while (currentToken.type == COMMA) {
            eat(COMMA);
            parameters.push_back(currentToken.text);
            eat(VARIABLE);
        }
    }
    return parameters;
}

// Function to parse a block of statements
std::vector<Token> Parser::parseBlock() {
    std::vector<Token> block;
    while (currentToken.type != BLOCK_END) {
        block.push_back(currentToken);
        parseStatement();
    }
    return block;
}

// Function to parse and evaluate expressions
int Parser::parseExpression() {
    int result = parseTerm();
    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        Token token = currentToken;
        if (token.type == PLUS) {
            eat(PLUS);
            result += parseTerm();
        } else if (token.type == MINUS) {
            eat(MINUS);
            result -= parseTerm();
        }
    }
    return result;
}

// Function to parse and evaluate terms
int Parser::parseTerm() {
    int result = parseFactor();
    while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE) {
        Token token = currentToken;
        if (token.type == MULTIPLY) {
            eat(MULTIPLY);
            result *= parseFactor();
        } else if (token.type == DIVIDE) {
            eat(DIVIDE);
            int right = parseFactor();
            if (right == 0) {
                std::cerr << "Division by zero" << std::endl;
                exit(1);
            }
            result /= right;
        }
    }
    return result;
}

// Function to parse and evaluate factors
int Parser::parseFactor() {
    Token token = currentToken;
    if (token.type == NUMBER) {
        eat(NUMBER);
        return std::stoi(token.text);
    } else if (token.type == VARIABLE) {
        eat(VARIABLE);
        return symbolTable.getVariable(token.text);
    } else if (token.type == LPAREN) {
        eat(LPAREN);
        int result = parseExpression();
        eat(RPAREN);
        return result;
    } else {
        std::cerr << "Invalid factor" << std::endl;
        exit(1);
    }
}