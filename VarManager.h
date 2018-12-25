#include <utility>

#ifndef PROJECT_VARMANAGER_H
#define PROJECT_VARMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Expression.h"
#include <mutex>
#include <pthread.h>
#include "DataReaderClient.h"

using namespace std;

class VarManager {

    map<string, double> _symbolTable;
    map<string, vector<string> > _binds;
    vector<string> _specialNames;

    DataReaderClient *_client;
    mutex lock;

public:
    VarManager() {
        _client = nullptr;
    };

    // Setters
    // set var value and only its value.
    void SetVarValue(const string &var, double value) {
        this->_symbolTable[var] = value;
    }

    void Bind(string source, string target);

    // update all binds of given path
    void UpdatePath(const string &path, double value);

    // updates a given var
    void UpdateVar(const string &varName, double value);

    // update all the binds of a given var
    void UpdateVarBinds(const string &varName);

    void SendSimulatorUpdate(const string &path, double value);

    void AddClient(DataReaderClient *newClient);

    // Getters
    double GetValue(const string &varName);

    // Infromation
    bool IsInSpecialNames(const string &name);

    bool IsLegal(const string &varName) {
        bool r = !IsVarExist(varName);
        bool l = !IsInSpecialNames(varName);
        return !IsVarExist(varName) && !IsInSpecialNames(varName);
    }

    bool IsVarExist(const string &var) {
        return !(this->_symbolTable.find(var) == this->_symbolTable.end());
    }

    bool IsBindExist(const string &source, const string &target);

    bool hasBind(const string &source);
};

#endif