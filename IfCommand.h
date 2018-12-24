#ifndef PROJECT_IFCOMMAND_H
#define PROJECT_IFCOMMAND_H

#include "ScopeCommand.h"

class IfCommand : public ScopeCommand {

    map<int, bool> _linesRecord;

public:

    IfCommand(DataHandler *_dataHandler, VarManager *_varManager,
              ShuntingYard *_expCalculator) : ScopeCommand(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {}

    bool ShouldStop() override;
};

#endif
