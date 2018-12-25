#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include "DataReaderServer.h"

#define LOAD_MSG "Please wait until the simulator loads completly, then press enter"

class OpenDataServerCommand : public Command {

    DataReaderServer *server;
public:

    OpenDataServerCommand(DataHandler *_dataHandler, VarManager *_varManager,
                          ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                                  _varManager,
                                                                  _expCalculator) {
        this->server = new DataReaderServer(_varManager);
    }

    void doCommand() override;

    ~OpenDataServerCommand() override {
        delete this->server;
    }
};


#endif
