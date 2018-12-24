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
#include "AndConditionalExpression.h"
#include "OrConditionalExpression.h"
#include "EqualConditionalExpression.h"
#include "NotEqualConditionalExpression.h"
#include "SmallConditionalExpression.h"
#include "SmallEqualConditionalExpression.h"
#include "BigConditionalExpression.h"
#include "BigEqualConditionalExpression.h"

using namespace std;

class ShuntingYard {
    VarManager *varManager;
    Tokenizer tokenizer;

    queue<Token> ShuntingYardAlgorithm(vector<Token> splitPhrase);

    Expression *CalculateQueue(queue<Token> queuE);

    Expression *getFitExp(const string &operation,
                          stack<Expression *> &stackExp);

public:

    ShuntingYard(VarManager *varManager) {
        this->varManager = varManager;
        this->tokenizer.SetShuntingYard();
    }

    double GetResults(string phrase) {
        Expression *e = GetExpression(phrase);
        double result = e->Calculate();
        delete e;
        return result;
    }

    Expression *GetExpression(string phrase) {
        vector<Token> splitPhrase = this->tokenizer.Lex(phrase);
        queue<Token> orderedTokens = ShuntingYardAlgorithm(splitPhrase);
        return CalculateQueue(orderedTokens);
    }
};

#endif
