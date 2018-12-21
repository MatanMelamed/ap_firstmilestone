//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_BIGEQUALCONDITIONALEXPRESSION_H
#define PROJECT_BIGEQUALCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class BigEqualConditionalExpression : public ConditionalExpression{
    Expression* exp1;
    Expression* exp2;
public:
    BigEqualConditionalExpression(Expression* expression1, Expression* expression2);
    double Calculate();
};



#endif //PROJECT_BIGEQUALCONDITIONALEXPRESSION_H
