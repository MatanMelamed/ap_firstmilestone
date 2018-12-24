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
            double *number = new double();
            if (_varManager->GetValue(value, number)) {
                string path = _varManager->GetPath(value);
                _varManager->SetValue(varName, *number);
                _varManager->SetBindBetweenVars(value, varName);

            } else {
                // get '=' token.
                SyntaxErrorHandler(_dataHandler->GetTokenInOffSet(-2));
            }
            delete number;
        }
    } else {
        string expression = _dataHandler->GetCurrentToken().get_value();
        double newValue = _expCalculator->GetResults(expression);
        _varManager->SetValue(varName, newValue);
        if (this->_varManager->hasBindVars(varName)) {
            vector<string> varsConected = this->_varManager->getBindedVars(
                    varName);
            for (const string &var: varsConected) {
                this->_varManager->SetValue(var, newValue);
            }
        }
    }

    this->_dataHandler->Advance(ONE);
}

