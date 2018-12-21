//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_SMALLEQUALCONDITIONALEXPRESSION_H
#define PROJECT_SMALLEQUALCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class SmallEqualConditionalExpression : public ConditionalExpression{
        Expression* exp1;
        Expression* exp2;
    public:
    SmallEqualConditionalExpression(Expression* expression1, Expression* expression2);
        double Calculate();
    };



#endif //PROJECT_SMALLEQUALCONDITIONALEXPRESSION_H
