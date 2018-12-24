#ifndef PROJECT_EXITCOMMAND_H
#define PROJECT_EXITCOMMAND_H

#include "Command.h"

class ExitCommand : public Command {

public:
    ExitCommand(DataHandler *_dataHandler, VarManager *_varManager,
                ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                        _varManager,
                                                        _expCalculator) {}

    void doCommand() override {
        _dataHandler->EraseAll();
    }

    ~ExitCommand() override = default;
};

#endif
