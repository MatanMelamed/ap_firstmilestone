#define SER_EXIST_ERR "Server already exists!"
#define CMD_AND_ARG_NUM 3

#include <iostream>
#include "OpenDataCommand.h"

int OpenDataCommand::doCommand(string *tokens, int index) {

    if (_called_already) {
        cout << SER_EXIST_ERR;
        return CMD_AND_ARG_NUM;
    }

    Params *p = new Params();
    p->port = 0; // get port
    p->freq = 0; //get freq
    _factory->SetServerParams(p);

    pthread_t ser_thrd;
    pthread_create(&ser_thrd, nullptr, CommandFactory::PowerServer, _factory);
    _called_already = true;

    return CMD_AND_ARG_NUM;
}

