//
// Created by tomme on 23/12/2018.
//

#include "DataReaderClient.h"

void DataReaderClient::ConnectClient(string ip, int port) {

    struct MyParams* params = new MyParams();
    params->ip = ip;
    params->port = port;
    params->data = this;
    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderClient::thread_func, params);
}
void* DataReaderClient::thread_func(void *arg) {
    struct MyParams *params = (struct MyParams *) arg;
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;




    portno = params->port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(params->ip.c_str());

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    /* Now ask for a message from the user, this message
       * will be read by server
    */
    while(!params->data->stop) {
        params->data->UpdateSimulator(sockfd);
    }
}

void DataReaderClient::UpdateSimulator(int sockfd){
    char buffer[1024];
    string pathToAllVars[XML_AMOUNT_VARS] = {INDICATE_SPD, INDICATE_ALT,
         PRESSURE_ALT, PITCH_DEG,ROLL_DEG, IN_PITCH_DEG,IN_ROLL_DEG,
         ENC_INDICATE_ALT,ENC_PRESURE_ALT, GPS_ALT,
         GPS_GRND_SPD, GPS_VERTICAL_SPD,HEAD_DEG, CMPS_HEAD_DEG,
         SLIP_SKID, TURN_RATE, SPEED_FPM,AILERON, ELEVATOR, RUDDER,
         FLAPS, THROTTLE, RPM};


    for (int i = 0; i < XML_AMOUNT_VARS; ++i) {
        if (this->_varManager->pathExist(pathToAllVars[i])) {
            vector<string> vars =
                    this->_varManager->getVarsOfPath(pathToAllVars[i]);
            for(int index = 0; index<vars.size();index++){
                double* number = new double();
                string value = to_string(this->_varManager->GetValue(vars[i],
                        number));
                string d = pathToAllVars[i].substr(1,pathToAllVars[i].length());
                d = d.substr(0,d.length()-1);
                string set = "set " + d +" "+value+"\r\n";
                int n = write(sockfd, set.c_str(), set.size());
                if (n < 0) {
                    perror("ERROR writing to socket");
                    exit(1);
                }
            }
        }
    }
}