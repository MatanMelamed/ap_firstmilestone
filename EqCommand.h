#ifndef PROJECT_EQCOMMAND_H
#define PROJECT_EQCOMMAND_H

#include "Command.h"

using namespace std;

class EqCommand : public Command {

public:
    EqCommand(DataHandler *_dataHandler, VarManager *_varManager,
              ShuntingYard *_expCalculator) : Command(_dataHandler, _varManager,
                                                      _expCalculator) {}

    void doCommand() override;
};

#endif
