#ifndef AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H
#define AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H

#include <map>
#include <string>

#include "Expression.h"
#include "VarManager.h"
#include "DataHandler.h"
#include "CommandFactory.h"

#include "CommandExpression.h"

#define UNKNOWN_CMD ", unknown command: "

using namespace std;

class ExpressionManager {

    VarManager _varManager;
    CommandFactory _factory;

    DataHandler *_dataHandler;

    map<string, Expression *> _knownExpressions;

    /**
     * return an expression with existing key.
     * if the expression is not yet created - create it and return it.
     */
    Expression *GetExpression(const string &exp);

    void LoadKnownExpressions();

public:

    ExpressionManager(DataHandler *dataHandler) : _factory(dataHandler) {
        this->_dataHandler = dataHandler;
        this->_factory.SetVarManager(&(this->_varManager));
        LoadKnownExpressions();
    }

    Expression *GetNextExpression();
};


#endif
