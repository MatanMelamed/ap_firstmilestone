//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_PLUS_H
#define PROJECT_PLUS_H


#include "BinaryExpression.h"

class Plus: public BinaryExpression {

private:
    Expression* exp1;
    Expression* exp2;
public:
    Plus(Expression* expression1, Expression* expression2);
    double Calculate();

};


#endif //PROJECT_PLUS_H
