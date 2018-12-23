
#ifndef PROJECT_VARMANAGER_H
#define PROJECT_VARMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Expression.h"

using namespace std;

class VarManager {

    map<string, double> _symbolTable;
    map<string,string> _pathConnected;
    map<string,vector<string>> _pathToVars;

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
    void SetPathAndVar(const string &path, string var) {
        this->_pathToVars[path].push_back(var);
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
        for(int i=0; i<this->_pathToVars[path].size();i++){
            string var = this->_pathToVars[path][i];
            this->_symbolTable[var] = value;
        }
    }
    bool pathExist(string path) {
        if(this->_pathToVars.count(path)>0){
            return true;
        }
        return false;
    }

};


#endif
