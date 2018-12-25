#ifndef PROJECT_DATAREADERSERVER_H
#define PROJECT_DATAREADERSERVER_H

#include "VarManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"

#define PATH_FILE "paths.txt"
#define MILI_SEC 1000

class DataReaderServer {

    map<int, string> _paths;
    VarManager *_varManager;
    bool stop;

public:
    struct ServerParams {
        int port;
        int hertz;
        int serverSocket;
    } params{};

    explicit DataReaderServer(VarManager *varManager) {
        this->_varManager = varManager;
        this->stop = false;
        LoadPaths();
    }

    void LoadPaths();

    void OpenServer(int port, int hertz);

    int CreateServerSocket(int port);

    void SendUpdate(vector<double> newData);

    static void *StartListeningForData(void *arg);

    void Try(string &buffer, string &c, string &l);

    void needToStop() {
        this->stop = true;
    }

};

#endif