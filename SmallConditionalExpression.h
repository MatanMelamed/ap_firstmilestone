#ifndef PROJECT_SMALLCONDITIONALEXPRESSION_H
#define PROJECT_SMALLCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class SmallConditionalExpression : public ConditionalExpression {
    Expression *exp1;
    Expression *exp2;
public:
    SmallConditionalExpression(Expression *expression1,
                               Expression *expression2);

    double Calculate() override;
};

#endif