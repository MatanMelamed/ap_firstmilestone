//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_MULT_H
#define PROJECT_MULT_H


#include "BinaryExpression.h"

class Mult : public BinaryExpression{
    Expression* exp1;
    Expression* exp2;
public:
    Mult(Expression* expression1, Expression* expression2);
    double Calculate();
};
#endif //PROJECT_MULT_H
