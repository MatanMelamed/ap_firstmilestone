
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
    map<string,string> _pathConnected;
    map<string,vector<string>> _pathToVars;
    mutex lock;

public:
    VarManager() {
    };

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

    void SetPath(const string &var, string path) {
        this->lock.lock();
        this->_pathConnected[var] = path;
        this->lock.unlock();
    }

    bool varHasPath(const string &var) {
        return !(this->_pathConnected.find(var) == this->_pathConnected.end());
    }
    string GetPath(const string &var) {
            string path = this->_pathConnected[var];
            return path;
    }
    void SetPathAndVar(string path, string var) {
        if(this->_pathToVars.count(path)>0) {
            this->_pathToVars[path].push_back(var);
        } else {
            string vaR = var;
            string patH = path;
            vector<string> vector1;
            vector1.push_back(vaR);
            this->_pathToVars[patH] = vector1;
        }
    }

    bool GetVarByPath(const string &path, string *var) {
        try {
            *var = this->_pathToVars[path][0];
            return true;
        } catch (const out_of_range &e) {
            return false;
        }

    }

    void UpdateAllVars(string path, double value) {
        this->lock.lock();
        for(int i=0; i<this->_pathToVars[path].size();i++){
            string var = this->_pathToVars[path][i];
            this->_symbolTable[var] = value;
        }
        this->lock.unlock();
    }
    bool pathExist(const string &path) {
        return !(this->_pathToVars.find(path) == this->_pathToVars.end());
    }
    vector<string> getVarsOfPath(string path){
        return this->_pathToVars[path];
    }
};


#endif
