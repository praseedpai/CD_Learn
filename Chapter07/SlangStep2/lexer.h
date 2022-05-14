#pragma once
#ifndef _LEXER_
#define _LEXER_
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

namespace lexer {
    enum Token {
        TOK_ILLEGAL_TOKEN = -1,
        TOK_PLUS, //+
        TOK_MINUS, //-
        TOK_MUL, //*
        TOK_DIV, // /
        TOK_OPAREN, // (
        TOK_CPAREN, // )
        TOK_DOUBLE,
        TOK_NULL
    };

    class Lexer {
        char* exp;
        int index;
        int length;
        long double number;

    public:
        Lexer(char* exp);
        ~Lexer();
        Token GetToken();
        double GetNumber();
    };
}

lexer::Lexer::Lexer(char* exp) {
    this->exp = exp;
    this->length = std::strlen(exp);
    this->index = 0;
}

//No resources need to be released
lexer::Lexer::~Lexer() {}

lexer::Token lexer::Lexer::GetToken() {
    Token tok = TOK_ILLEGAL_TOKEN;

    //Skip white space
    while (index < length && (exp[index] == ' ' || exp[index] == '\t')) {
        index++;
    }

    //End of string return null
    if (index == length) {
        return TOK_NULL;
    }

    switch (exp[index]) {
    case '+':
        tok = TOK_PLUS;
        index++;
        break;
    case '-':
        tok = TOK_MINUS;
        index++;
        break;
    case '*':
        tok = TOK_MUL;
        index++;
        break;
    case '/':
        tok = TOK_DIV;
        index++;
        break;
    case '(':
        tok = TOK_OPAREN;
        index++;
        break;
    case ')':
        tok = TOK_CPAREN;
        index++;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        int numStartIndex = index;
        int numEndIndex;
        while (index < length && (
            exp[index] == '0' ||
            exp[index] == '1' ||
            exp[index] == '2' ||
            exp[index] == '3' ||
            exp[index] == '4' ||
            exp[index] == '5' ||
            exp[index] == '6' ||
            exp[index] == '7' ||
            exp[index] == '8' ||
            exp[index] == '9')) {
            index++;
        }
        numEndIndex = index;
        size_t lenOfNum = numEndIndex - numStartIndex;
        number = std::stold((exp + numStartIndex), &lenOfNum);
        tok = TOK_DOUBLE;
        
        break;
    }
    default:
        throw std::runtime_error("Unknown character found while tokenizing ");
    }

    return tok;
}

double lexer::Lexer::GetNumber() {
    return number;
}
#endif