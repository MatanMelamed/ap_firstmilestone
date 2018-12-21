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
        strings->push_back("var");
        strings->push_back("gog");
        strings->push_back("=");
        strings->push_back("bind");
        strings->push_back("john/cena");
        strings->push_back("var");
        strings->push_back("djKhaled");
        strings->push_back("=");
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

