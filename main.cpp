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
        //l.Interpret();
        vector<string>* strings = new vector<string>;;
        strings->push_back("print");
        strings->push_back("\"Matan&Tom\"");
        strings->push_back("connect");
        strings->push_back("127.0.0.1");
        strings->push_back("5402");
        strings->push_back("openDataServer");
        strings->push_back("5400");
        strings->push_back("3");
        dataHandler.SetData(strings);

        Parser(&dataHandler, &expressionManager);
        int x =3;
        break;
    }

};


void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager) {
    while (dataHandler->hasMoreStrings()) {
        expressionManager->GetNextExpression()->Calculate();
    }
}

