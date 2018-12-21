#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H

#include "Command.h"
#include <iostream>

using namespace std;

class PrintCommand : public Command {
public:
    PrintCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() {
        _dataHandler->Advance(1);
        string toPrint = _dataHandler->GetCurrentToken().get_value();
        if (toPrint[0] == '\"') {
            string stringToShow = toPrint.substr(1, toPrint.length());
            stringToShow = stringToShow.substr(0, stringToShow.length() - 1);
            cout << stringToShow << endl;
        }
        else {
            //calculte expression
        }
        _dataHandler->Advance(1);
    }
};


#endif
