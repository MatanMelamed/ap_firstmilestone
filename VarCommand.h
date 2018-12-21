
#ifndef PROJECT_VARCOMMAND_H
#define PROJECT_VARCOMMAND_H

#include "Command.h"

#define INIT_VAL 0
#define ONE 1

class VarCommand : public Command {

public:

    VarCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    double doCommand() override {

        this->_dataHandler->Advance(ONE);
        Token newVar = this->_dataHandler->GetCurrentToken();
        // if valid

        this->_varManager->SetValue(newVar.get_value(), INIT_VAL);
        this->_dataHandler->Advance(ONE);
        return 0;
    }

};

#endif
