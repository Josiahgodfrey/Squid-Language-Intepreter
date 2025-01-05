#include "Interpreter.h"

int main() {
    std::string input = "print 1 + 2 * 3;";
    Interpreter interpreter(input);
    interpreter.interpret();

    return 0;
}