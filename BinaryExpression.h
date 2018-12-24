#ifndef PROJECT_BINARYEXPRESSION_H
#define PROJECT_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
    Expression *exp1;
    Expression *exp2;

    virtual double Calculate() = 0;

};

#endif
