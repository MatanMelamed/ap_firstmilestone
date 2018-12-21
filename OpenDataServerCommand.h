#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#include "Command.h"

class OpenDataServerCommand : public Command {
public:
    OpenDataServerCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() {
        _dataHandler->Advance(ONE);
        string port = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(ONE);
        string hertz = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(ONE);
    }
};


#endif
