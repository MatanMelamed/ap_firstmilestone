//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_SMALLCONDITIONALEXPRESSION_H
#define PROJECT_SMALLCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class SmallConditionalExpression : public ConditionalExpression {
    Expression* exp1;
    Expression* exp2;
public:
    SmallConditionalExpression(Expression* expression1, Expression* expression2);
    double Calculate();
};


#endif //PROJECT_SMALLCONDITIONALEXPRESSION_H
