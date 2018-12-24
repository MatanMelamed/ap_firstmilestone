#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include <string>
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

    Command *GetCommand(const string &name);

    void SetVarManager(VarManager *varManager) {
        this->_varManager = varManager;
        this->_expressionCalculator = new ShuntingYard(varManager);
    }

    virtual ~CommandFactory();
};

#endif
