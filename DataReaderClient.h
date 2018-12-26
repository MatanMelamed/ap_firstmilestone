#ifndef PROJECT_DATAREADERCLIENT_H
#define PROJECT_DATAREADERCLIENT_H

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <mutex>

#include <string.h>
#include <string>
#include <queue>
#include <iostream>

#define ADD_TASK "add"
#define GET_TASK "get"

using namespace std;

struct UpdateUnit {
    string path;
    double value;
};

class DataReaderClient {

    bool _stop;
    queue<UpdateUnit> _neededUpdates;
    mutex lock;

public:
    struct ClientParams {
        string _ip;
        int _port;
        int _sockdf;
        pthread_t _pthread;
    } _params;

    DataReaderClient() {
        _stop = false;
    };

    pthread_t StartClient(const string &ip, int port);

    static void *UpdateStatus(void *arg);

    void ConnectToSimulator();

    void SendToSimulator(int sockfd);

    UpdateUnit RequestTask(UpdateUnit update, string request);

    bool ShouldStop();

    void Stop() {
        _stop = true;
    }

};


#endif