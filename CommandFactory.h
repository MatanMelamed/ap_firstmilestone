#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include "DataHandler.h"
#include "Command.h"
#include "VarCommand.h"

#include <string>

using namespace std;

class CommandFactory {

    DataHandler *_dataHandler;
    VarManager *_varManager;

public:

    CommandFactory(DataHandler *dataHandler) {
        this->_dataHandler = dataHandler;
        this->_varManager = nullptr;
    }

    Command *GetCommand(const string &name) {
        Command *target;
        if (name == "var" || name == "Var") {
            target = new VarCommand(this->_dataHandler, this->_varManager);
        }
        return target;
    }

    void SetVarManager(VarManager *varManager) {
        this->_varManager = varManager;
    }

};

#endif
