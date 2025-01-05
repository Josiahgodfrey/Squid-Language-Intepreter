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
            std::string variable = "";
            while (position < input.length() && isalpha(input[position])) {
                variable += input[position];
                position++;
            }
            return Token(VARIABLE, variable);
        }

        // comment handling

        if (currentChar == ' ') {
            if (position + 1 < input.length() && input[position + 1] == '#') {
                // Skip the rest of the line
                while (position < input.length() && input[position] != '\n') {
                    position++;
                }
            } else {
                // Invalid character
                std::cerr << "Invalid character: " << currentChar << std::endl;
                exit(1);
            }
        }

        // String literal handling

        if (currentChar == '"') {
            std::string literal = "";
            position++;
            while (position < input.length() && input[position] != '"') {
                literal += input[position];
                position++;
            }
            if (position < input.length()) {
                position++;
                return Token(STRING, literal);
            } else {
                // Unterminated string literal
                std::cerr << "Unterminated string literal" << std::endl;
                exit(1);
            }
        }

        // Handling keywords

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

        // Token identifier handling

        else if (currentChar == '^') {
            position++;
            return Token(POWER, "^");
        } else if (currentChar == '&') {
            position++;
            return Token(AND, "&");
        } else if (currentChar == '|') {
            position++;
            return Token(OR, "|");
        } else if (currentChar == '!') {
            position++;
            return Token(NOT, "!");
        }

        else if (currentChar == '"') {
            position++;
            std::string text;

            while (currentChar != '"') {
                if (currentChar == '\\') {
                    position++;
                    if (currentChar == '"') {
                        text += '"';
                    }
                    else if (currentChar == '\\') {
                        text += '\\';
                    }
                    else if (currentChar == 'n') {
                        text += '\n';
                    }
                    // Add support for other escape sequences as needed
                }
                else {
                    text += currentChar;
                }
                position++;
            }

            position++;
            return Token(STRING, text);
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
            default:
                std::cerr << "Invalid character: " << currentChar << std::endl;
                exit(1);
        }
    }

    return Token(END, "");
}