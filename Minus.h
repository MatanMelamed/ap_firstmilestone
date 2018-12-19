//
// Created by tomme on 14/12/2018.
//

#ifndef EXPRESSIONSPROJECT_MINUS_H
#define EXPRESSIONSPROJECT_MINUS_H


#include "../../Desktop/ap_firstmilestone/BinaryExpression.h"

class Minus: public BinaryExpression {
    Expression* exp1;
    Expression* exp2;
public:
    Minus(Expression* expression1, Expression* expression2);
    double calculate();
};


#endif //EXPRESSIONSPROJECT_MINUS_H
