
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Define your token types here
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
    std::string value;
};

#endif // TOKEN_H// Token.h