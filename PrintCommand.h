//
// Created by tomme on 20/12/2018.
//

#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H
//
// Created by tomme on 20/12/2018.
//

#define ONE 1
#define TWO 2

#include "Command.h"
#include <iostream>
using namespace std;

class PrintCommand: public Command {
public:
    PrintCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    double doCommand() {
        _dataHandler->Advance(1);
        Token toPrint = _dataHandler->GetCurrentToken();
        if(toPrint.get_value()[0]=='\"'){
            string stringToShow = toPrint.get_value().substr(1,
                    toPrint.get_value().length());
            stringToShow = stringToShow.substr(0,stringToShow.length()-1);
            cout<<stringToShow<<endl;
        } else{
            //calculte expression
        }
        _dataHandler->Advance(1);
        return 0;
    }
};


#endif //PROJECT_PRINTCOMMAND_H
