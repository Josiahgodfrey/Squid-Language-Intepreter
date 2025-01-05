#include "Parser.h"

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = lexer.getNextToken();
    } else {
        std::cerr << "Unexpected token: " << currentToken.text << std::endl;
        exit(1);
    }
}

int Parser::factor() {
    Token token = currentToken;

    if (token.type == NUMBER) {
        eat(NUMBER);
        return std::stoi(token.text);
    } else if (token.type == VARIABLE) {
        eat(VARIABLE);
        // Lookup the value of the variable in the symbol table
        // Return the value
        return symbolTable.getVariable(token.text);
    } else if (token.type == LPAREN) {
        eat(LPAREN);
        int result = expr();
        eat(RPAREN);
        return result;
    } else {
        std::cerr << "Invalid factor" << std::endl;
        exit(1);
    }
}

int Parser::term() {
    int result = factor();

    while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE) {
        Token token = currentToken;

        if (token.type == MULTIPLY) {
            eat(MULTIPLY);
            result *= factor();
        } else if (token.type == DIVIDE) {
            eat(DIVIDE);
            result /= factor();
        }
    }

    return result;
}

// Modifying the Parser class to handle additional operators
int Parser::expr() {
    int result = term();

    while (currentToken.type == PLUS || currentToken.type == MINUS ||
           currentToken.type == MULTIPLY || currentToken.type == DIVIDE ||
           currentToken.type == POWER || currentToken.type == AND ||
           currentToken.type == OR || currentToken.type == NOT) {
        Token token = currentToken;

        if (token.type == PLUS) {
            eat(PLUS);
            result += term();
        }
        else if (token.type == MINUS) {
            eat(MINUS);
            result -= term();
        }
        else if (token.type == MULTIPLY) {
            eat(MULTIPLY);
            result *= term();
        }
        else if (token.type == DIVIDE) {
            eat(DIVIDE);
            result /= term();
        }
        else if (token.type == POWER) {
            eat(POWER);
            result = pow(result, term());
        }
        else if (token.type == AND) {
            eat(AND);
            result = result && term();
        }
        else if (token.type == OR) {
            eat(OR);
            result = result || term();
        }
        else if (token.type == NOT) {
            eat(NOT);
            result = !term();
        }
    }

    return result;
}


// Modifying the Parser class to handle variable declarations and assignments
void Parser::parseVariableDeclaration() {
    eat(VARIABLE);
    std::string name = currentToken.text;
    eat(ASSIGN);
    int value = expr();
    symbolTable.addVariable(name, value);
}


// Modifying the Parser class to handle string literals
int Parser::parseString() {
    Token token = currentToken;

    if (token.type == STRING) {
        eat(STRING);
        // Perform any necessary operations with the string literal
        return 0; // Replace with actual code
    }
    else {
        std::cerr << "Invalid token: " << token.text << std::endl;
        exit(1);
    }
}

// Modify the Parser class to handle syntax errors
void Parser::parse() {
    try {
        while (currentToken.type != EOF) {
            // Parse and execute statements
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Syntax error: " << e.what() << std::endl;
        exit(1);
    }
}

// Modifying the Parser class to handle type errors
int Parser::expr() {
    int result = term();

    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        Token token = currentToken;

        if (token.type == PLUS) {
            eat(PLUS);
            int right = term();

            if (std::isinf(result) || std::isinf(right)) {
                throw std::runtime_error("Integer overflow");
            }

            result += right;
        }
        else if (token.type == MINUS) {
            eat(MINUS);
            int right = term();

            if (std::isinf(result) || std::isinf(right)) {
                throw std::runtime_error("Integer overflow");
            }

            result -= right;
        }
    }

    return result;
}

// Modifying the Parser class to handle nested expressions
int Parser::expr() {
    int result = term();

    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        Token token = currentToken;

        if (token.type == PLUS) {
            eat(PLUS);
            result += term();
        }
        else if (token.type == MINUS) {
            eat(MINUS);
            result -= term();
        }
    }

    return result;
}

// Modifying the Parser class to handle operator precedence
int Parser::term() {
    int result = factor();

    while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE) {
        Token token = currentToken;

        if (token.type == MULTIPLY) {
            eat(MULTIPLY);
            result *= factor();
        }
        else if (token.type == DIVIDE) {
            eat(DIVIDE);
            int right = factor();

            if (right == 0) {
                throw std::runtime_error("Division by zero");
            }

            result /= right;
        }
    }

    return result;
}
