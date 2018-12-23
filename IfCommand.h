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

    bool ShouldStop() override {
        bool result = true;
        int currentLineNumber = _dataHandler->GetCurrentLineIndex();

        /**
         * each if statement will be checked twice for one run on it.
         * once for the first time, then make it depend on the condition.
         * second time if after reaching its end of scope,
         * then of course don't bother checking the condition.
         * but reset if statement,
         * if it will be checked again it will only be in a loop.
         */
        if (!_linesRecord[currentLineNumber]) {
            result = _condition->Calculate() == 0;
            _linesRecord[currentLineNumber] = true;
        } else {
            _linesRecord[currentLineNumber] = false;
        }

        return result;
    }
};

#endif
