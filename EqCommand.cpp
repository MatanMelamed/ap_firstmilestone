#include "EqCommand.h"

void EqCommand::doCommand() {
    _dataHandler->Advance(MINUS_ONE);
    string varName = _dataHandler->GetCurrentToken().get_value();

    _dataHandler->Advance(TWO);
    string value = _dataHandler->GetCurrentToken().get_value();

    if (value == "bind") {
        _dataHandler->Advance(ONE);
        value = this->_dataHandler->GetCurrentToken().get_value();
        if (value[0] == '\'') {
            _varManager->SetPath(varName, value);
            _varManager->SetPathAndVar(value, varName);
        } else {
            if (_varManager->IsExist(value)) {
                string path = _varManager->GetPath(value);
                _varManager->SetPath(varName, path);
                _varManager->SetPathAndVar(path, varName);

            } else {
                // get '=' token.
                SyntaxErrorHandler(_dataHandler->GetTokenInOffSet(-2));
            }
        }
    } else {
        string expression = _dataHandler->GetCurrentToken().get_value();
        double newValue = _expCalculator->GetResults(expression);
        _varManager->SetValue(varName, newValue);
    }

    this->_dataHandler->Advance(ONE);
}

