#ifndef PROJECT_DIV_H
#define PROJECT_DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {
    Expression *exp1;
    Expression *exp2;
public:
    Div(Expression *expression1, Expression *expression2);

    double Calculate();
};

#endif
