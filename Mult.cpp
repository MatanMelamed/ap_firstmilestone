//
// Created by tomme on 14/12/2018.
//

#include "Mult.h"

Mult::Mult(Expression* expression1, Expression* expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double Mult::calculate() {
    return this->exp1->calculate() * this->exp2->calculate();
}
