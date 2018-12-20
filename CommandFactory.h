#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include "DataHandler.h"
#include "Command.h"
#include "VarCommand.h"

#include <string>

using namespace std;

class CommandFactory {

    DataHandler *_dataHandler;

public:

    CommandFactory(DataHandler *dataHandler) {
        this->_dataHandler = dataHandler;
    }

    Command *GetCommand(const string &name) {
        Command *target;
        if (name == "var" || name == "Var") {
            target = new VarCommand();
        } else if (name == "all commands..") {

        }

        target->SetDataHandler(this->_dataHandler);
        return target;
    }

};

#endif
