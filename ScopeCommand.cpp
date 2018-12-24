#include "ScopeCommand.h"

void ScopeCommand::doCommand() {
    SetScope();

    // if scope ready then run the command
    if (_dataHandler->IsScopeReady(_start_line)) {
        if (ShouldStop()) {
            _dataHandler->SkipCurrentScope();
        } else {
            _dataHandler->GoToNextLine();
        }
    } else {
        _dataHandler->BuildScope();
    }
}

void ScopeCommand::SetScope() {
    this->_start_line = _dataHandler->GetCurrentLineIndex();
    this->_condition = _expCalculator->GetExpression(
            _dataHandler->GetTokenInOffSet(ONE).get_value());
}

ScopeCommand::~ScopeCommand() {
    delete _condition;
}
