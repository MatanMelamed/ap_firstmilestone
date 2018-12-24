#include "DataReaderServer.h"
#include <iostream>
#include <string>

#define NUM_OF_PATHS 23

using namespace std;

void DataReaderServer::OpenServer(int port, int time) {
    cout << "Please wait until simulator is opened";
    int serverSocket = this->CreateServerSocket(port);
    cin.get();
    struct MyParams *params = new MyParams();
    params->port = port;
    params->hertz = time;
    params->serverSocket = serverSocket;
    params->data = this;
    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderServer::thread_func, params);
}

void *DataReaderServer::thread_func(void *arg) {
    struct MyParams *params = (struct MyParams *) arg;
    int n;
    char buffer[256];

    /* If connection is established then start communicating */
    while (!params->data->stop) {

        bzero(buffer, 256);
        n = read(params->serverSocket, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        vector<double> convertedInfo = StringToInfo(buffer);
        params->data->UpdateSymbleTable(convertedInfo);

        sleep(params->hertz / MILI_SEC);
    }

    delete params;
    return nullptr;
}

vector<double> DataReaderServer::StringToInfo(string input) {

    vector<double> result;
    string sum;
    int index = 0;

    while (result.size() == NUM_OF_PATHS) {
        if (input[index] == ',' || input[index] == '\n') {
            result.push_back(stod(sum));
            sum.clear();
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

void DataReaderServer::UpdateSymbleTable(vector<double> convertedInfo) {
    string pathToAllVars[XML_AMOUNT_VARS] = {INDICATE_SPD, INDICATE_ALT,
                                             PRESSURE_ALT, PITCH_DEG, ROLL_DEG,
                                             IN_PITCH_DEG, IN_ROLL_DEG,
                                             ENC_INDICATE_ALT, ENC_PRESURE_ALT,
                                             GPS_ALT,
                                             GPS_GRND_SPD, GPS_VERTICAL_SPD,
                                             HEAD_DEG, CMPS_HEAD_DEG,
                                             SLIP_SKID, TURN_RATE, SPEED_FPM,
                                             AILERON, ELEVATOR, RUDDER,
                                             FLAPS, THROTTLE, RPM};
    for (int i = 0; i <= XML_AMOUNT_VARS; ++i) {
        if (this->_varManager->pathExist(pathToAllVars[i])) {
            this->_varManager->UpdateAllVars(pathToAllVars[i],
                                             convertedInfo[i]);
        }
    }
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
