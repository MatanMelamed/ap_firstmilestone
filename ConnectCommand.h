#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H

#include "Command.h"

class ConnectCommand : public Command {

public:
    ConnectCommand(DataHandler *_dataHandler, VarManager *_varManager,
                   ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {}

    void doCommand() override {
        _dataHandler->Advance(1);
        string ip = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(1);
        string port = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(1);
    }
};

#endif