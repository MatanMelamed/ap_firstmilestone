//
// Created by tomme on 14/12/2018.
//

#ifndef EXPRESSIONSPROJECT_PLUS_H
#define EXPRESSIONSPROJECT_PLUS_H


#include "../../Desktop/ap_firstmilestone/BinaryExpression.h"
#

class Plus: public BinaryExpression {

private:
    Expression* exp1;
    Expression* exp2;
public:
    Plus(Expression* expression1, Expression* expression2);
    double calculate();

};


#endif //EXPRESSIONSPROJECT_PLUS_H
