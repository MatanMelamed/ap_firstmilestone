#ifndef PROJECT_EQCOMMAND_H
#define PROJECT_EQCOMMAND_H

#include "Command.h"

using namespace std;

class EqCommand : public Command {

public:
    EqCommand(DataHandler *_dataHandler, VarManager *_varManager,
              ShuntingYard *_expCalculator) : Command(_dataHandler, _varManager,
                                                      _expCalculator) {}

    void doCommand() override {

        _dataHandler->Advance(RESET_LINE_INDEX);
        string varName = _dataHandler->GetCurrentToken().get_value();

        _dataHandler->Advance(TWO);
        string value = _dataHandler->GetCurrentToken().get_value();

        if (value == "bind") {
            _dataHandler->Advance(ONE);
            value = this->_dataHandler->GetCurrentToken().get_value();
            _varManager->SetPath(varName, value);
        } else {
            //change it to get Expression
            string expression = _dataHandler->GetCurrentToken().get_value();
            double newValue = _expCalculator->GetResults(expression);
            _varManager->SetValue(varName, newValue);
        }

        this->_dataHandler->Advance(ONE);
    }
};

#endif
