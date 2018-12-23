#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H

#define ONE 1
#define TWO 2

#include "Command.h"
#include <iostream>

using namespace std;

class PrintCommand : public Command {

public:
    PrintCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {}

    void doCommand() override {
        _dataHandler->Advance(ONE);
        Token toPrint = _dataHandler->GetCurrentToken();
        if (toPrint.get_value()[0] == '\"') {
            string stringToShow = toPrint.get_value().substr(1,
                                                             toPrint.get_value().length());
            stringToShow = stringToShow.substr(0, stringToShow.length() - 1);
            cout << stringToShow << endl;
        } else {
            cout << _expCalculator->GetResults(toPrint.get_value()) << endl;
        }
        _dataHandler->Advance(1);
    }
};


#endif
