#include "ConnectCommand.h"

void ConnectCommand::doCommand() {
    _dataHandler->Advance(ONE);
    string ip = _dataHandler->GetCurrentToken().get_value();
    _dataHandler->Advance(ONE);
    string portString = _dataHandler->GetCurrentToken().get_value();
    double port = _expCalculator->GetExpression(portString)->Calculate();
    _dataHandler->Advance(ONE);

    client->StartClient(ip, (int) port);
    _varManager->AddClient(client);
}
