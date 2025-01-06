#include <iostream>
#include "Interpreter.h"
#include <fstream>

std::string readInput() {
    // Implement the logic to read the input from a file or from user input

    // Example: Read the input from a file
    std::ifstream file("INPUT.txt");
    std::string input;
    std::getline(file, input);
    file.close();

    return input;
}

std::string interpret() {
    
}
int main() {
    readInput();
    // Read the input from a file or from user input
    std::string input = readInput();

    // Create an instance of the Interpreter
    Interpreter interpreter(input);

    // Interpret the dunny program
    interpreter.interpret();

    return 0;
}
