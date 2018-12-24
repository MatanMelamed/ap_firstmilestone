#include "VarManager.h"

bool VarManager::IsInSpecialNames(const string &name) {
    bool result = false;
    vector<string>::iterator it;
    for (it = _specialNames.begin(); it != _specialNames.end(); ++it) {
        if ((*it) == name) {
            result = true;
            break;
        }
    }
    return result;
}

bool VarManager::GetValue(const string &var, double *target) {
    try {
        *target = this->_symbolTable[var];
        return true;
    } catch (const out_of_range &e) {
        return false;
    }
}

bool VarManager::GetVarByPath(const string &path, string *var) {
    try {
        *var = this->_pathToVars[path][0];
        return true;
    } catch (const out_of_range &e) {
        return false;
    }
}

void VarManager::UpdateAllVars(string path, double value) {
    this->lock.lock();
    for (int i = 0; i < this->_pathToVars[path].size(); i++) {
        string var = this->_pathToVars[path][i];
        this->_symbolTable[var] = value;
    }
    this->lock.unlock();
}
