#ifndef PROJECT_ORCONDITIONALEXPRESSION_H
#define PROJECT_ORCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class OrConditionalExpression : public ConditionalExpression {
    Expression *exp1;
    Expression *exp2;
public:
    OrConditionalExpression(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif