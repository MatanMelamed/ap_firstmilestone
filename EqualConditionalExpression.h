#ifndef PROJECT_EQUALCONDITIONALEXPRESSION_H
#define PROJECT_EQUALCONDITIONALEXPRESSION_H

#include "ConditionalExpression.h"

class EqualConditionalExpression : public ConditionalExpression {
    Expression *exp1;
    Expression *exp2;
public:
    EqualConditionalExpression(Expression *expression1,
                               Expression *expression2);

    double Calculate() override;
};


#endif
