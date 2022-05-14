#pragma once
#ifndef _PARSER_
#define _PARSER_

#include <stdexcept>
#include "ast.h"
#include "lexer.h"

using namespace lexer;
using namespace ast;

namespace parser {
	class RDParser : public Lexer {
		Token currentToken;
	
	public:
		RDParser(char* exp);
		~RDParser();

		Exp* CallExp();
		Exp* Expr();
		Exp* Term();
		Exp* Factor();
	};
}

parser::RDParser::RDParser(char* exp): Lexer(exp) {}

//No resources need to be released
parser::RDParser::~RDParser(){}

Exp* parser::RDParser::CallExp() {
	currentToken = GetToken();
	return Expr();
}

Exp* parser::RDParser::Expr() {
	Token lToken;
	Exp* retValue = Term();

	while (currentToken == TOK_PLUS || currentToken == TOK_MINUS) {
		lToken = currentToken;
		currentToken = GetToken();
		Exp* right = Expr();
		retValue = new BinaryExp(retValue, right, lToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
	}

	return retValue;
}

Exp* parser::RDParser::Term() {
	Token lToken;
	Exp* retValue = Factor();

	while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
		lToken = currentToken;
		currentToken = GetToken();
		Exp* right = Factor();
		retValue = new BinaryExp(retValue, right, lToken == TOK_MUL ? OP_MUL : OP_DIV);
	}

	return retValue;
}

Exp* parser::RDParser::Factor() {
	Exp* retValue;

	if (currentToken == TOK_DOUBLE) {
		retValue = new NumericConstant(GetNumber());
		currentToken = GetToken();
	} 
	else if (currentToken == TOK_OPAREN) {
		currentToken = GetToken();
		retValue = Expr();

		if (currentToken != TOK_CPAREN) {
			if (retValue) delete retValue;
			throw std::runtime_error("Missing closing paranthesis");
		}

		currentToken = GetToken();
	}
	else if (currentToken == TOK_PLUS || currentToken == TOK_MINUS) {
		Token lToken = currentToken;
		currentToken = GetToken();
		retValue = Factor();
		retValue = new UnaryExp(retValue, lToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
	}
	else {
		throw std::runtime_error("Illegal token");
	}

	return retValue;
}

#endif