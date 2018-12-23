#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#define ONE 1

#include "Command.h"

class OpenDataServerCommand: public Command{
public:

    OpenDataServerCommand(DataHandler *_dataHandler, VarManager *_varManager,
                          ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                                  _varManager,
                                                                  _expCalculator) {}

    void doCommand() override {
        _dataHandler->Advance(1);
        Token port = _dataHandler->GetCurrentToken();
        _dataHandler->Advance(1);
        Token hertz =  _dataHandler->GetCurrentToken();
        _dataHandler->Advance(1);
    }
};


#endif
