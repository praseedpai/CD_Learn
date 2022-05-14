#pragma once
#ifndef _AST_
#include <iostream>
#include <stdexcept>
#define _AST_
namespace ast {

    class RuntimeContext {
    public:
        RuntimeContext() {}
    };

    class Exp {
    public:
        Exp();
        virtual double Evaluate(RuntimeContext* cont) = 0;
        virtual ~Exp();;
    };

    enum Operator {
        OP_PLUS, OP_MINUS, OP_DIV, OP_MUL
    };

    class NumericConstant : public Exp {
        double value;

    public:
        NumericConstant(double value);
        virtual double Evaluate(RuntimeContext* cont);
        virtual ~NumericConstant();

    };

    class BinaryExp : public Exp {
        Exp* left, * right;
        Operator op;

    public:
        BinaryExp(Exp* left, Exp* right, Operator op);
        virtual double Evaluate(RuntimeContext* cont);
        virtual ~BinaryExp();

    };

    class UnaryExp : public Exp {
        Exp* exp;
        Operator op;

    public:
        UnaryExp(Exp* exp, Operator op);
        virtual double Evaluate(RuntimeContext* cont);
        virtual ~UnaryExp();
    };
};

ast::Exp::Exp() {}

ast::Exp::~Exp() {}

ast::NumericConstant::NumericConstant(double value) {
    this->value = value;
}

double ast::NumericConstant::Evaluate(RuntimeContext* cont) {
    return value;
}

ast::NumericConstant::~NumericConstant() {}


ast::BinaryExp::BinaryExp(Exp* left, Exp* right, Operator op) {
    this->left = left;
    this->right = right;
    this->op = op;
}

double ast::BinaryExp::Evaluate(RuntimeContext* cont) {
    switch (op) {
    case OP_PLUS:
        return left->Evaluate(cont) + right->Evaluate(cont);
    case OP_MINUS:
        return left->Evaluate(cont) - right->Evaluate(cont);
    case OP_DIV:
        return left->Evaluate(cont) / right->Evaluate(cont);
    case OP_MUL:
        return left->Evaluate(cont) * right->Evaluate(cont);
    default:
        throw std::runtime_error("Unknown operator");
    }
}

ast::BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}

ast::UnaryExp::UnaryExp(Exp* exp, Operator op) {
    this->exp = exp;
    this->op = op;
}

double ast::UnaryExp::Evaluate(RuntimeContext* cont) {
    switch (op) {
    case OP_PLUS:
        return exp->Evaluate(cont);
    case OP_MINUS:
        return -exp->Evaluate(cont);

    default:
        throw std::runtime_error("Unsupported operator");
    }
}

ast::UnaryExp::~UnaryExp() {
    delete exp;
}
#endif