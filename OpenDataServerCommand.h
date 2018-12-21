//
// Created by tomme on 20/12/2018.
//

#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#define ONE 1

#include "Command.h"

class OpenDataServerCommand: public Command{
public:
    OpenDataServerCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    double doCommand() {
        _dataHandler->Advance(1);
        string port = _dataHandler->GetCurrentString();
        _dataHandler->Advance(1);
        string hertz =  _dataHandler->GetCurrentString();
        _dataHandler->Advance(1);
        return 0;
    }
};


#endif //PROJECT_OPENDATASERVERCOMMAND_H
