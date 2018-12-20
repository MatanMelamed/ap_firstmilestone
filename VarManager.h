
#ifndef PROJECT_VARMANAGER_H
#define PROJECT_VARMANAGER_H

#include <map>
#include <string>

#include "Expression.h"

using namespace std;

class VarManager {

    map<string, double> _symbolTable;

public:
    VarManager() {};

    void SetValue(const string &var, double value) {
        this->_symbolTable[var] = value;
    }

    bool isExist(const string &var) {
        return !(this->_symbolTable.find(var) == this->_symbolTable.end());
    }

    bool GetValue(const string &var, double *target) {
        try {
            *target = this->_symbolTable[var];
            return true;
        } catch (const out_of_range &e) {
            return false;
        }
    }
};


#endif
