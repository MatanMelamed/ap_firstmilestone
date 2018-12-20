#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include "DataHandler.h"
#include "Command.h"
#include "VarCommand.h"
#include "EqCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "OpenDataServerCommand.h"
#include "ConnectCommand.h"
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
        if(name=="=") {
            target = new EqCommand(this->_dataHandler,this->_varManager);
        }
        if(name=="sleep" || name == "Sleep") {
            target = new SleepCommand(this->_dataHandler,this->_varManager);
        }
        if(name=="print" || name == "Print") {
            target = new PrintCommand(this->_dataHandler,this->_varManager);
        }
        if(name=="openDataServer" || name == "OpenDataServer") {
            target = new OpenDataServerCommand(this->_dataHandler,this->_varManager);
        }
        if(name=="connect" || name == "Connect") {
            target = new ConnectCommand(this->_dataHandler,this->_varManager);
        }
        return target;
    }

    void SetVarManager(VarManager *varManager) {
        this->_varManager = varManager;
    }

};

#endif
