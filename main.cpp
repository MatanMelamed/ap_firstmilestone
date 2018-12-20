#include <iostream>
#include <string>
#include <vector>

#include "ExpressionManager.h"
#include "Expression.h"
#include "DataHandler.h"

#include "Lexer.h"


using namespace std;

void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager);

int main(int args, char **argv) {

    DataHandler dataHandler;
    ExpressionManager expressionManager(&dataHandler);
    string target = args == 2 ? argv[1] : NOT_FILE;
    Lexer l = Lexer(&dataHandler, &expressionManager, target);

    while (true) {

        // loads dataHandler with new splitted vector of strings
        // either from file or from command line
        l.Interpret();

        Parser(&dataHandler, &expressionManager);
    }

};


void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager) {
    while (dataHandler->hasMoreStrings()) {
        expressionManager->GetNextExpression()->Calculate();
    }
}

