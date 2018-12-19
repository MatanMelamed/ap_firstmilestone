
#ifndef TRY_COMMANDFACTORY_H
#define TRY_COMMANDFACTORY_H

#include "DataServer.h"
#include "VarCommand.h"
#include "Params.h"

class CommandFactory {

    DataServer *_server;
    Params *_p;
    VarCommand *_varManager;

public:

    void SetServerParams(Params *params);

    static void *PowerServer(void *args);

    Command *GetCommandByName(string name);


};


#endif
