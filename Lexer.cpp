#include "Lexer.h"

struct Token {
    TokenType type;
    std::string text;

    Token(TokenType type, std::string text) : type(type), text(text) {}
};

Token Lexer::getNextToken() {
    while (position < input.length()) {
        char currentChar = input[position];

        if (isspace(currentChar)) {
            position++;
            continue;
        }

        if (isdigit(currentChar)) {
            std::string number = "";
            while (position < input.length() && isdigit(input[position])) {
                number += input[position];
                position++;
            }
            return Token(NUMBER, number);
        }

        if (isalpha(currentChar)) {
            std::string identifier = "";
            while (position < input.length() && isalpha(input[position])) {
                identifier += input[position];
                position++;
            }

            if (identifier == "if") {
                return Token(IF, identifier);
            } else if (identifier == "else") {
                return Token(ELSE, identifier);
            } else if (identifier == "while") {
                return Token(WHILE, identifier);
            } else if (identifier == "for") {
                return Token(FOR, identifier);
            } else {
                return Token(VARIABLE, identifier);
            }
        }

        if (currentChar == '"') {
            std::string literal = "";
            position++;
            while (position < input.length() && input[position] != '"') {
                if (input[position] == '\\') {
                    position++;
                    if (position < input.length()) {
                        literal += input[position];
                    }
                } else {
                    literal += input[position];
                }
                position++;
            }
            if (position < input.length()) {
                position++;
                return Token(STRING, literal);
            } else {
                std::cerr << "Unterminated string literal" << std::endl;
                exit(1);
            }
        }

        switch (currentChar) {
            case '+':
                position++;
                return Token(PLUS, "+");
            case '-':
                position++;
                return Token(MINUS, "-");
            case '*':
                position++;
                return Token(MULTIPLY, "*");
            case '/':
                position++;
                return Token(DIVIDE, "/");
            case '=':
                position++;
                return Token(ASSIGN, "=");
            case ';':
                position++;
                return Token(PRINT, ";");
            case '^':
                position++;
                return Token(POWER, "^");
            case '&':
                position++;
                return Token(AND, "&");
            case '|':
                position++;
                return Token(OR, "|");
            case '!':
                position++;
                return Token(NOT, "!");
            default:
                std::cerr << "Invalid character: " << currentChar << std::endl;
                exit(1);
        }
    }

    return Token(END, "");
}
