#ifndef PROJECT_SCOPECOMMAND_H
#define PROJECT_SCOPECOMMAND_H


#include "Command.h"
#include <list>
#include "ExpressionManager.h"

class ScopeCommand : public Command {

    int _start_line;
protected:
    Expression *_condition;

public:
    ScopeCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {
        this->_condition = nullptr;
    }

    void doCommand() override {
        SetScope();

        // if scope ready then run the command
        if (_dataHandler->IsScopeReady(_start_line)) {
            if (ShouldStop()) {
                _dataHandler->SkipCurrentScope();
            } else {
                _dataHandler->GoToNextLine();
            }
        } else {
            _dataHandler->StartRead();
        }
    }

    /**
    * set scope parameters
    */
    void SetScope() {
        this->_start_line = _dataHandler->GetCurrentLineIndex();
        this->_condition = _expCalculator->GetExpression(
                _dataHandler->GetTokenInOffSet(ONE).get_value());
    }

    virtual bool ShouldStop() = 0;

};


#endif
