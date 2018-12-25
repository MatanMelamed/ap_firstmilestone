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
#include <stack>
#include <iostream>

using namespace std;

struct UpdateUnit {
    string path;
    double value;
};

class DataReaderClient {

    bool _stop;
    stack<UpdateUnit> _neededUpdates;
    mutex lock;

public:
    struct ClientParams {
        string _ip;
        int _port;
        int _sockdf;
        pthread_t _pthread;
    } _params;

    DataReaderClient() {};

    void StartClient(const string &ip, int port);

    static void *UpdateStatus(void *arg);

    void ConnectToSimulator();

    void SendToSimulator(int sockfd);

    void AddTask(UpdateUnit update) {
        _neededUpdates.push(update);
    }

    bool ShouldStop();

};


#endif