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
#include "AndCondtitionalExpression.h"
#include "OrConditionalExpression.h"
#include "EqualConditionalExpression.h"
#include "NotEqualConditionalExpression.h"
#include "SmallConditionalExpression.h"
#include "SmallEqualConditionalExpression.h"
#include "BigConditionalExpression.h"
#include "BigEqualConditionalExpression.h"

using namespace std;

class ShuntingYard {
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
            bool flag = false;
            if(token.get_type()==NUM || token.get_type() ==STR) {
                queuE.push(token);
            }
            if(token.get_type()==MATH ||token.get_type()==BOOL) {
                if(stacK.empty() || token.get_value()=="(") {
                    stacK.push(token);
                } else {
                    if (token.get_value() == ")") {
                        Token token1 = stacK.top();
                        while (token1.get_value() != "(" || stacK.empty()) {
                            queuE.push(token1);
                            stacK.pop();
                            if (!stacK.empty()) {
                                token1 = stacK.top();
                            } else {
                                break;
                            }
                        }
                        stacK.pop();
                        flag = true;
                    }
                    if (!flag) {
                        Token token1 = stacK.top();
                        while ((token1.getPriority() >= token.getPriority()) &&
                               !stacK.empty()) {
                            queuE.push(token1);
                            stacK.pop();
                            if (!stacK.empty()) {
                                token1 = stacK.top();
                            } else {
                                break;
                            }
                        }
                        if (token.get_value() == ")") {
                            stacK.pop();
                        } else {
                            stacK.push(token);
                        }

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
        stack<Expression*> stackExp;
        vector<Token>vecToken;
        Expression* temp;
        while(!queuE.empty()) {
            Token token = queuE.front();
            vecToken.push_back(token);
            queuE.pop();
        }
        for(int index= 0; index<vecToken.size();index++){
            Token token = vecToken[index];
            if(token.get_type()== NUM){
                stackExp.push(new Number(stod(token.get_value())));
            }
            else {
                if (token.get_type() == STR) {
                    if (this->varManager->isExist(token.get_value())) {
                        double *number = new double();
                        this->varManager->GetValue(token.get_value(),number);
                        stackExp.push(new Number(*number));
                        delete number;
                    } else {
                        throw "no valid variable";
                    }
                } else {
                    try {
                        stackExp.push(getFitExp(token.get_value(),stackExp));
                    } catch (const out_of_range &e) {
                        cout<<"Something is wrong with the input";
                    }
                }
            }
        }
        Expression* expression = stackExp.top();
        stackExp.pop();
        double result = expression->Calculate();
        delete expression;
        return result;

    }
    Expression* getFitExp(string operation,stack<Expression*>& stackExp ){
        Expression* rightExp=nullptr;
        Expression* leftExp=nullptr;
        rightExp = stackExp.top();
        stackExp.pop();
        if(!stackExp.empty()) {
            leftExp = stackExp.top();
            stackExp.pop();
        } else {
            leftExp=new Number(0);
        }

        if(operation == "+") {
            return new Plus(leftExp,rightExp);
        }
        if(operation == "-") {
            return new Minus(leftExp,rightExp);
        }
        if(operation == "*") {
            return new Mult(leftExp,rightExp);
        }
        if(operation == "/") {
            return new Div(leftExp,rightExp);
        }
        if(operation == "&&") {
            return new AndCondtitionalExpression(leftExp,rightExp);
        }
        if(operation == "||") {
            return new OrConditionalExpression(leftExp,rightExp);
        }
        if(operation == "<") {
            return new SmallConditionalExpression(leftExp,rightExp);
        }
        if(operation == "<=") {
            return new SmallEqualConditionalExpression(leftExp,rightExp);
        }
        if(operation == ">") {
            return new BigConditionalExpression(leftExp,rightExp);
        }
        if(operation == ">=") {
            return new BigEqualConditionalExpression(leftExp,rightExp);
        }
        if(operation == "==") {
            return new EqualConditionalExpression(leftExp,rightExp);
        }
        if(operation == "!=") {
            return new NotEqualConditionalExpression(leftExp,rightExp);
        }
    }
};
#endif //PROJECT_SHUNTINGYARD_H
