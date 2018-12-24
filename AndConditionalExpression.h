#ifndef PROJECT_ANDCONDITIONALEXPRESSION_H
#define PROJECT_ANDCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class AndConditionalExpression : public ConditionalExpression {
    Expression *exp1;
    Expression *exp2;
public:
    AndConditionalExpression(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif
