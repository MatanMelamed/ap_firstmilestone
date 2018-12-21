#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H

#include "Command.h"

class ConnectCommand : public Command {
public:
    ConnectCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() {
        _dataHandler->Advance(1);
        string ip = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(1);
        string port = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(1);
    }
};

#endif