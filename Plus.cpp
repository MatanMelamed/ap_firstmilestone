//
// Created by tomme on 21/12/2018.
//

#include "Plus.h"

Plus::Plus(Expression* expression1, Expression* expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double Plus::Calculate() {
    return this->exp1->Calculate() + this->exp2->Calculate();
}