//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_ANDCONDTITIONALEXPRESSION_H
#define PROJECT_ANDCONDTITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class AndCondtitionalExpression : public ConditionalExpression {
    Expression* exp1;
    Expression* exp2;
public:
    AndCondtitionalExpression(Expression* expression1, Expression* expression2);
    double Calculate();
};



#endif //PROJECT_ANDCONDTITIONALEXPRESSION_H
