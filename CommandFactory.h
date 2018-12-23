#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include <string>
#include "DataHandler.h"
#include "ShuntingYard.h"

#include "VarCommand.h"
#include "EqCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "OpenDataServerCommand.h"
#include "ConnectCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"


using namespace std;

class CommandFactory {

    DataHandler *_dataHandler;
    VarManager *_varManager;
    ShuntingYard *_expressionCalculator;

public:

    explicit CommandFactory(DataHandler *dataHandler) {
        this->_dataHandler = dataHandler;
        this->_varManager = nullptr;
        this->_expressionCalculator = nullptr;
    }

    Command *GetCommand(const string &name) {
        Command *target;
        if (name == "var" || name == "Var") {
            target = new VarCommand(this->_dataHandler, this->_varManager,
                                    this->_expressionCalculator);
        } else if (name == "=") {
            target = new EqCommand(this->_dataHandler, this->_varManager,
                                   this->_expressionCalculator);
        } else if (name == "sleep" || name == "Sleep") {
            target = new SleepCommand(this->_dataHandler, this->_varManager,
                                      this->_expressionCalculator);
        } else if (name == "print" || name == "Print") {
            target = new PrintCommand(this->_dataHandler, this->_varManager,
                                      this->_expressionCalculator);
        } else if (name == "openDataServer" || name == "OpenDataServer") {
            target = new OpenDataServerCommand(this->_dataHandler,
                                               this->_varManager,
                                               this->_expressionCalculator);
        } else if (name == "connect" || name == "Connect") {
            target = new ConnectCommand(this->_dataHandler, this->_varManager,
                                        this->_expressionCalculator);
        } else if (name == "while") {
            target = new WhileCommand(this->_dataHandler, this->_varManager,
                                      this->_expressionCalculator);
        } else if (name == "if") {
            target = new IfCommand(this->_dataHandler, this->_varManager,
                                   this->_expressionCalculator);
        }
        return target;
    }

    void SetVarManager(VarManager *varManager) {
        this->_varManager = varManager;
        this->_expressionCalculator = new ShuntingYard(varManager);
    }

};

#endif
