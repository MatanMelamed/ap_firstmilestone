//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_BIGCONDITIONALEXPRESSION_H
#define PROJECT_BIGCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class BigConditionalExpression : public ConditionalExpression {
    Expression* exp1;
    Expression* exp2;
public:
    BigConditionalExpression(Expression* expression1, Expression* expression2);
    double Calculate();
};



#endif //PROJECT_BIGCONDITIONALEXPRESSION_H