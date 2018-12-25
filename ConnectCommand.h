#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H

#include "Command.h"
#include "DataReaderClient.h"

class ConnectCommand : public Command {

    DataReaderClient *client;
public:
    ConnectCommand(DataHandler *_dataHandler, VarManager *_varManager,
                   ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {
        client = new DataReaderClient();
    }

    void doCommand() override;

    ~ConnectCommand() override {
        delete this->client;
    }
};

#endif