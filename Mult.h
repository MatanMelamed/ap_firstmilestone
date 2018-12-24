#ifndef PROJECT_MULT_H
#define PROJECT_MULT_H

#include "BinaryExpression.h"

class Mult : public BinaryExpression {
    Expression *exp1;
    Expression *exp2;
public:
    Mult(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif