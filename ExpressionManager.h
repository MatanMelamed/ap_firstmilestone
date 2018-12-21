#ifndef AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H
#define AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H

#include <map>
#include <string>

#include "Expression.h"
#include "VarManager.h"
#include "DataHandler.h"
#include "CommandFactory.h"
#include "CommandExpression.h"


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
    Expression *GetExpression(const string &exp) {
        Expression *target = _knownExpressions[exp];

        if (target == nullptr) {
            target = new CommandExpression(_factory.GetCommand(exp));
            _knownExpressions[exp] = target;
        }

        return target;
    }

    void LoadKnownExpressions() {
        _knownExpressions["var"] = nullptr;
        _knownExpressions["="] = nullptr;
        _knownExpressions["sleep"] = nullptr;
        _knownExpressions["print"] = nullptr;
        _knownExpressions["openDataServer"] = nullptr;
        _knownExpressions["connect"] = nullptr;
    }

public:

    ExpressionManager(DataHandler *dataHandler) : _factory(dataHandler) {
        this->_dataHandler = dataHandler;
        this->_factory.SetVarManager(&(this->_varManager));
        LoadKnownExpressions();
    }

    Expression *GetNextExpression() {
        string exp = _dataHandler->GetCurrentToken().get_value();

        if (!(_knownExpressions.find(exp) == _knownExpressions.end())) {
            // is an expression in map
            return GetExpression(exp);
        }

        else { // is not an expression, may be var - check next

            _dataHandler->Advance(NEXT);
            exp = _dataHandler->GetCurrentToken().get_value();

            if (!(_knownExpressions.find(exp) == _knownExpressions.end())) {
                return GetExpression(exp);
            }

            else {
                // syntax error
            }
        }

    }

};


#endif
