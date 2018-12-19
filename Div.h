//
// Created by tomme on 14/12/2018.
//

#ifndef EXPRESSIONSPROJECT_DIV_H
#define EXPRESSIONSPROJECT_DIV_H
#include "../../Desktop/ap_firstmilestone/BinaryExpression.h"

class Div : public BinaryExpression {
    Expression* exp1;
    Expression* exp2;
public:
    Div(Expression* expression1, Expression* expression2);
    double calculate();
};


#endif //EXPRESSIONSPROJECT_DIV_H
