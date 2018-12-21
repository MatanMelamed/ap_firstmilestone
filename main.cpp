#include <iostream>
#include <string>
#include <vector>

#include "ExpressionManager.h"
#include "Expression.h"
#include "DataHandler.h"

#include "Lexer.h"


using namespace std;

void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager);

int asd(int args, char **argv) {

    DataHandler dataHandler;
    ExpressionManager expressionManager(&dataHandler);
    string target = args == TWO ? argv[ONE] : NOT_FILE;
    Lexer l = Lexer(&dataHandler, target);

    while (true) {

        // loads dataHandler with new splitted vector of strings
        // either from file or from command line
        //l.Interpret();
        auto *strings = new vector<Token>;;
        strings->push_back(Token(STR, "var", 0, "", ""));
        dataHandler.SetNewLine(strings);

        Parser(&dataHandler, &expressionManager);
        int x = 3;
        break;
    }

};


void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager) {
    while (dataHandler->hasMoreTokens()) {
        expressionManager->GetNextExpression()->Calculate();
    }
}

