#ifndef PROJECT_HELP_H
#define PROJECT_HELP_H

#include "Command.h"

class HelpCommand : public Command {

public:
    HelpCommand(DataHandler *_dataHandler, VarManager *_varManager,
                ShuntingYard *_expCalculator = nullptr) : Command(_dataHandler,
                                                                  _varManager,
                                                                  _expCalculator) {}

    void doCommand() override {
        _varManager->PrintAll();
        _dataHandler->Advance(ONE);
    }
};

#endif
