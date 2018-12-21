//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_NUMBER_H
#define PROJECT_NUMBER_H

#include "Expression.h"

class Number: public Expression {
private:
    double num;
public:
    Number(double number);
    double Calculate();

};


#endif //PROJECT_NUMBER_H
