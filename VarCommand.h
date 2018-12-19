#ifndef TRY_VARCOMMAND_H
#define TRY_VARCOMMAND_H

#include <map>
#include <string>
#include "Command.h"

using namespace std;

class VarCommand : public Command {

    map<string, double> symbolTable;

public:

    VarCommand() = default;

    int doCommand(string *tokens, int index);

    bool SetVarValue(string name, double value);

    bool GetVarValue(string name, double *value);

};

#endif

