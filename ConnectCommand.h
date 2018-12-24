#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H

#include "Command.h"
#include "DataReaderClient.h"

class ConnectCommand : public Command {
private:
    DataReaderClient *client;
public:
    ConnectCommand(DataHandler *_dataHandler, VarManager *_varManager,
                   ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {
        client = new DataReaderClient(_varManager);
    }

    void doCommand() override {
        _dataHandler->Advance(ONE);
        string ip = _dataHandler->GetCurrentToken().get_value();
        _dataHandler->Advance(ONE);
        string portString = _dataHandler->GetCurrentToken().get_value();
        double port = _expCalculator->GetExpression(portString)->Calculate();
        _dataHandler->Advance(ONE);
        this->client->ConnectClient(ip, port);
    }

    ~ConnectCommand() {
        delete this->client;
    }
};

#endif