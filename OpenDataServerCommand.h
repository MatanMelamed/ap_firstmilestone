#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#define ONE 1

#include "Command.h"
#include "DataReaderServer.h"

class OpenDataServerCommand: public Command{
private:
    DataReaderServer* server;
public:

    OpenDataServerCommand(DataHandler *_dataHandler, VarManager *_varManager,
                  ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                          _varManager,
                                                          _expCalculator) {
            this->server = new DataReaderServer(_varManager);
    }

    void doCommand() override {
        _dataHandler->Advance(1);
        string portString = _dataHandler->GetCurrentToken().get_value();
        double port = _expCalculator->GetExpression(portString)->Calculate();
        _dataHandler->Advance(1);
        string hertzString = _dataHandler->GetCurrentToken().get_value();
        double hertz = _expCalculator->GetExpression(hertzString)->Calculate();
        _dataHandler->Advance(1);
        this->server->OpenServer(port,hertz);
    }
    ~OpenDataServerCommand(){
            delete this->server;
    }
};


#endif
