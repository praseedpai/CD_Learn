#include <iostream>
#include "lexer.h"

using namespace lexer;

int main() {
    char expStr[] = " 1 2 + - / * ( ) 9831337  ";
    Lexer *lexer = new Lexer(expStr);
    Token token;
    while ((token = lexer->GetToken()) != TOK_NULL) {
        std::cout << token << std::endl;
        if (token == TOK_DOUBLE) {
            std::cout << "Number: " << lexer->GetNumber() << std::endl;
        }
    }

    delete lexer;
}