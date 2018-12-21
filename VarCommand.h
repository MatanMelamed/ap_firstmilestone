
#ifndef PROJECT_VARCOMMAND_H
#define PROJECT_VARCOMMAND_H

#include "Command.h"

#define INVALID_NAME "var name must not contains numbers."
#define INIT_VAL 0
#define ONE 1

class VarCommand : public Command {


    bool hasNumber(const string &name) {
        bool result = false;
        for (char c : name) {
            if (48 <= c && c <= 57) {
                result = true;
                break;
            }
        }
        return result;
    }

public:

    VarCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() override {

        this->_dataHandler->Advance(ONE);
        string newVarName = this->_dataHandler->GetCurrentToken().get_value();

        if (!hasNumber(newVarName)) {
            this->_varManager->SetValue(newVarName, INIT_VAL);
            this->_dataHandler->Advance(ONE);
        }
        else {
            cout << INVALID_NAME;
        }
    }
};

#endif
