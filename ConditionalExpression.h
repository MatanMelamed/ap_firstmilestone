//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_CONDITIONALEXPRESSION_H
#define PROJECT_CONDITIONALEXPRESSION_H

#include "Expression.h"

class ConditionalExpression:public Expression{
    Expression* exp1;
    Expression* exp2;
    virtual double Calculate()=0;

};
#endif //PROJECT_CONDITIONALEXPRESSION_H
