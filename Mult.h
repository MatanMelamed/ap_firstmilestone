//
// Created by tomme on 14/12/2018.
//

#ifndef EXPRESSIONSPROJECT_MULT_H
#define EXPRESSIONSPROJECT_MULT_H

#include "../../Desktop/ap_firstmilestone/BinaryExpression.h"

class Mult : public BinaryExpression{
    Expression* exp1;
    Expression* exp2;
public:
    Mult(Expression* expression1, Expression* expression2);
    double calculate();
};


#endif //EXPRESSIONSPROJECT_MULT_H
