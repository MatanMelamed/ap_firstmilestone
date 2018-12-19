//
// Created by tomme on 14/12/2018.
//
#include "../../Desktop/ap_firstmilestone/Expression.h"
#ifndef EXPRESSIONSPROJECT_NUMBER_H
#define EXPRESSIONSPROJECT_NUMBER_H


class Number: public Expression {
private:
    double num;
public:
    Number(double number);
    double calculate();

};


#endif //EXPRESSIONSPROJECT_NUMBER_H
