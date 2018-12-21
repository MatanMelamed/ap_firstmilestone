//
// Created by tomme on 20/12/2018.
//

#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H
#define ONE 1

#include "Command.h"

class ConnectCommand: public Command{
public:
    ConnectCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() {
        _dataHandler->Advance(1);
        string ip = _dataHandler->GetCurrentString();
        _dataHandler->Advance(1);
        string port =  _dataHandler->GetCurrentString();
        _dataHandler->Advance(1);
    }
};
#endif //PROJECT_CONNECTCOMMAND_H
