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

vector<string> VarManager:: GetVarsByPath(string path) {
    return this->_pathToVars[path];
}

void VarManager::UpdateAllVars(string path, double value) {
    vector<string> vars = GetVarsByPath(path);
    lock.lock();
    for(string var: vars) {
        this->SetValue(var,value);
    }
    lock.unlock();
}
bool VarManager::hasBindVars(string var) {
    return !(this->_varToVars.find(var) == this->_varToVars.end());
}

vector<string> VarManager::getBindedVars(string var) {
    return  this->_varToVars[var];
}
void VarManager::SetBindBetweenVars(string sourceVar,string targetVar){
    this->_varToVars[sourceVar].push_back(targetVar);
}