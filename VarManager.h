#include <utility>

#ifndef PROJECT_VARMANAGER_H
#define PROJECT_VARMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Expression.h"
#include <mutex>
#include <pthread.h>

using namespace std;

class VarManager {

    map<string, double> _symbolTable;
    map<string, string> _pathConnected;
    map<string, vector<string>> _pathToVars;
    map<string,vector<string>> _varToVars;
    mutex lock;
    vector<string> _specialNames;

public:
    VarManager() {};

    bool IsInSpecialNames(const string &name);

    bool IsLegal(const string &varName) {
        bool r =!IsExist(varName);
        bool l=!IsInSpecialNames(varName);
        return !IsExist(varName) && !IsInSpecialNames(varName);
    }

    void SetValue(const string &var, double value) {
        this->_symbolTable[var] = value;
    }

    bool IsExist(const string &var) {
        return !(this->_symbolTable.find(var) == this->_symbolTable.end());
    }

    bool GetValue(const string &var, double *target);

    void SetPath(const string &var, string path) {
        this->_pathConnected[var] = path;
    }

    bool varHasPath(const string &var) {
        return !(this->_pathConnected.find(var) == this->_pathConnected.end());
    }

    string GetPath(const string &var) {
        string path = this->_pathConnected[var];
        return path;
    }

    void SetPathAndVar(const string &path, const string &var) {
        this->_pathToVars[path].push_back(var);
    }

    bool GetVarByPath(const string &path, string *var);

    void UpdateAllVars(string path, double value);

    bool pathExist(const string &path) {
        bool r = !(this->_pathToVars.find(path) == this->_pathToVars.end());
        return !(this->_pathToVars.find(path) == this->_pathToVars.end());
    }

    vector<string> getVarsOfPath(const string &path) {
        return this->_pathToVars[path];
}
    bool hasBindVars(string var);
    vector<string> getBindedVars(string var);
    vector<string> GetVarsByPath(string path);
    void SetBindBetweenVars(string sourceVar,string targetVar);
};

#endif