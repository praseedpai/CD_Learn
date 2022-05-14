#include <iostream>
#include "builder.h"

using namespace builder;

int main() {
    char expStr[] = " 1 + 4 / 2 + 1 ";
    ExpressionBuilder builder(expStr);
    Exp* exp = builder.GetExpression();
    if (exp) {
        std::cout << exp->Evaluate(NULL) << std::endl;
        delete exp;
    }
    else {  
        std::cout << "Unable to parse the expression: " << expStr << std::endl;
    }
}