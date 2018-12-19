#ifndef TRY_SERVER_H
#define TRY_SERVER_H

#include <string>
#include "Utils.h"
#include "VarCommand.h"
#include <map>
#include <netinet/in.h>
#include "Params.h"

using namespace std;


class DataServer {

    int sockfd, newsockfd, portno, client;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    map<string, double> _data;  //path to value
    map<string, string> _binds; //path to var name

    VarCommand *_varManager;

public:

    DataServer(VarCommand *varManager) {
        pop(&_data);
        _varManager = varManager;
    };

    void Init(Params *params);

    void ListenForClient();

    void ReceiveData();

};


#endif
