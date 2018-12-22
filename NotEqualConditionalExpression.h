//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_NOTEQUALCONDITIONALEXPRESSION_H
#define PROJECT_NOTEQUALCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class NotEqualConditionalExpression : public ConditionalExpression{
    Expression* exp1;
    Expression* exp2;
public:
    NotEqualConditionalExpression(Expression* expression1,
            Expression* expression2);
    double Calculate();
};


#endif //PROJECT_NOTEQUALCONDITIONALEXPRESSION_H