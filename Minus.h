//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_MINUS_H
#define PROJECT_MINUS_H

#include "BinaryExpression.h"

class Minus: public BinaryExpression {
    Expression* exp1;
    Expression* exp2;
public:
    Minus(Expression* expression1, Expression* expression2);
    double Calculate();
};


#endif //PROJECT_MINUS_H
