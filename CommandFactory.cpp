#include "CommandFactory.h"
#include "OpenDataCommand.h"


#define VAR_CMD_INVKR "var"
#define ODS_CMD_INVKR "openDataServer"
#define EQ_CMD_INVKR "="
#define SLP_CMD_INVKR "sleep"

void *CommandFactory::PowerServer(void *args) {

    auto *factory = (CommandFactory *) args;

    factory->_server = new DataServer(factory->_varManager);

    factory->_server->ListenForClient();

    factory->_server->


    return nullptr;
}

void CommandFactory::SetServerParams(Params *params) {
    _p = params;
}

Command *CommandFactory::GetCommandByName(string command) {

    if (command == VAR_CMD_INVKR) {
        if (_varManager == nullptr) {
            _varManager = new VarCommand();
        }
        return _varManager;
    }
    if (command == ODS_CMD_INVKR) {
        //Server creation depends on var manager so create it first.
        if (_varManager == nullptr) { _varManager = new VarCommand(); }

        return new OpenDataCommand(this);
    }


    return nullptr;
}

