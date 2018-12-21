//
// Created by tomme on 21/12/2018.
//

#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H

#include <string>
#include <map>
#include "Expression.h"
#include <regex>
#include "VarManager.h"
#include "Tokenizer.h"
#include "Token.h"
#include <queue>
#include "Div.h"
#include "Mult.h"
#include "Plus.h"
#include "Minus.h"
#include "Number.h"

using namespace std;

class ShuntingYard {
    map<string,int> priority;
    VarManager* varManager;
    Tokenizer* tokenizer;
public:
    ShuntingYard(VarManager* varManager) {
        this->varManager = varManager;
        this->tokenizer = new Tokenizer();
        this->tokenizer->SetShuntingYard();
    }
    double getResult(string phrase) {
        vector<Token> splitPhrase = this->tokenizer->Lex(phrase);
        queue<Token> queuE = ShuntingYardAlgorithm(splitPhrase);
        return CalculateQueue(queuE);
    }

     queue<Token> ShuntingYardAlgorithm(vector<Token>splitPhrase){
        stack<Token> stacK;
        queue<Token> queuE;
        for(Token token: splitPhrase) {
            if(token.get_type()==NUM || token.get_type() ==STR) {
                queuE.push(token);
            }
            if(token.get_type()==MATH) {
                if(stacK.empty()) {
                    stacK.push(token);
                } else {
                    Token token1 = stacK.top();
                    while((token1.getPriority() > token.getPriority()) &&
                                                            !stacK.empty()) {
                        queuE.push(token1);
                        stacK.pop();
                        if(!stacK.empty()) {
                            token1 = stacK.top();
                        } else {
                            break;
                        }
                    }
                    if(token.get_value()==")") {
                        stacK.pop();
                    }
                    else{
                        stacK.push(token);
                    }

                }
            }
        }
        while(!stacK.empty()) {
            Token newToken = stacK.top();
            queuE.push(newToken);
            stacK.pop();
        }
         return queuE;
    }

    double CalculateQueue(queue<Token> queuE) {
        queue<Expression*> ququeExp;
        while(!queuE.empty()) {
            Token token = queuE.front();
            if(token.get_type()== NUM){
                ququeExp.push(new Number(stod(token.get_value())));
            }
            else {
                if (token.get_type() == STR) {
                    if (this->varManager->isExist(token.get_value())) {
                        double *number = new double();
                        this->varManager->GetValue(token.get_value(),number);
                        ququeExp.push(new Number(*number));
                        delete number;
                    } else {
                        throw "no valid variable";
                    }
                } else {
                    try {
                        ququeExp.push(getFitExp(token.get_value(),
                                ququeExp));
                    } catch (const out_of_range &e) {
                        cout<<"Something is wrong with the input";
                    }
                }
            }
            queuE.pop();
            if(!queuE.empty()) {
                token = queuE.front();
            }
        }
        Expression* expression = ququeExp.front();
        double result = expression->Calculate();
        delete expression;
        return result;

    }
    Expression* getFitExp(string operation,queue<Expression*>& ququeExp ){
        Expression* leftExp = ququeExp.front();
        ququeExp.pop();
        Expression* rightExp = ququeExp.front();
        ququeExp.pop();
        if(operation == "+") {
            return new Plus(leftExp,rightExp);
        }
        if(operation == "-") {
            return new Minus(leftExp,rightExp);
        }
        if(operation == "*") {
            return new Mult(leftExp,rightExp);
        }
        if(operation == "+") {
            return new Div(leftExp,rightExp);
        }
    }
};
#endif //PROJECT_SHUNTINGYARD_H
