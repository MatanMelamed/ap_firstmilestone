#include "DataReaderServer.h"

using namespace std;

void DataReaderServer::OpenServer(int port, int time) {
    int serverSocket = CreateServerSocket(port);
    cin.get();
    params.port = port;
    params.hertz = time;
    params.serverSocket = serverSocket;

    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderServer::ReceiveNewData, this);
}

void *DataReaderServer::ReceiveNewData(void *arg) {
    auto *server = (DataReaderServer *) arg;
    int numOfReceivedBytes;
    char buffer[256];

    /* If connection is established then start communicating */
    while (!server->stop) {

        bzero(buffer, 256);
        numOfReceivedBytes = (int) read(server->params.serverSocket, buffer,
                                        255);
        if (numOfReceivedBytes < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        vector<double> convertedInfo = StringToInfo(buffer);
        server->SendUpdate(convertedInfo);

        sleep(server->params.hertz / MILI_SEC);
    }

    return nullptr;
}

vector<double> DataReaderServer::StringToInfo(string input) {

    vector<double> result;
    string sum;
    sum.clear();
    int index = 0;


    while (input[index]!='\n') {
        if (input[index] == ',') {
            if (!sum.empty()) {
                result.push_back(stod(sum));
                sum.clear();
            }
        } else {
            sum += input[index];
        }
        index++;
    }

    if (!sum.empty()) {
        result.push_back(stod(sum));
    }

    return result;
}

int DataReaderServer::CreateServerSocket(int port) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    return newsockfd;
}

void DataReaderServer::SendUpdate(vector<double> newData) {
    vector<double>::iterator it;
    int index = 0;
    for (it = newData.begin(); it != newData.end(); ++it) {
        if (_varManager->hasBind(_paths[index])) {
            _varManager->UpdatePath(_paths[index], (*it));
        }
    }
}

void DataReaderServer::LoadPaths() {
    ifstream file(PATH_FILE);
    int index = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            _paths[index] = line;
            index++;
        }
        file.close();
    }
}
