#pragma once

#ifndef _BUILDER_
#define _BUILDER_

#include <stdexcept>
#include <iostream>

#include "parser.h"
#include "ast.h"

using namespace parser;
using namespace ast;

namespace builder {
	class AbstractBuilder{};

	class ExpressionBuilder : public AbstractBuilder {
		char* exp;

	public:
		ExpressionBuilder(char* exp);
		~ExpressionBuilder();

		Exp* GetExpression();
	};
}

builder::ExpressionBuilder::ExpressionBuilder(char* exp) {
	this->exp = exp;
}

builder::ExpressionBuilder::~ExpressionBuilder() {}

Exp* builder::ExpressionBuilder::GetExpression() {
	try {
		RDParser parser(exp);
		return parser.CallExp();
	}
	catch (std::exception& e) {
		std::cout << "Exception occured: " << e.what() << std::endl;
	}

	return NULL;
}

#endif // !_BUILDER_
