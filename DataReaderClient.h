//
// Created by tomme on 23/12/2018.
//

#ifndef PROJECT_DATAREADERCLIENT_H
#define PROJECT_DATAREADERCLIENT_H

#include "VarManager.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

//windows
#define INDICATE_SPD "\"/instrumentation/airspeed-indicator/indicated-speed-kt\""
#define INDICATE_ALT "\"/instrumentation/altimeter/indicated-altitude-ft\""
#define PRESSURE_ALT "\"/instrumentation/altimeter/pressure-alt-ft\""
#define PITCH_DEG "\"/instrumentation/attitude-indicator/indicated-pitch-deg\""
#define ROLL_DEG "\"/instrumentation/attitude-indicator/indicated-roll-deg"
#define IN_PITCH_DEG "\"/instrumentation/attitude-indicator/internal-pitch-deg\""
#define IN_ROLL_DEG "\"/instrumentation/attitude-indicator/internal-roll-deg\""
#define ENC_INDICATE_ALT "\"/instrumentation/encoder/indicated-altitude-ft\""
#define ENC_PRESURE_ALT "\"/instrumentation/encoder/pressure-alt-ft\""
#define GPS_ALT "\"/instrumentation/gps/indicated-altitude-ft\""
#define GPS_GRND_SPD "\"/instrumentation/gps/indicated-ground-speed-kt\""
#define GPS_VERTICAL_SPD "\"/instrumentation/gps/indicated-vertical-speed\""
#define HEAD_DEG "\"/instrumentation/heading-indicator/indicated-heading-deg\""
#define CMPS_HEAD_DEG "\"/instrumentation/magnetic-compass/indicated-heading-deg\""
#define SLIP_SKID "\"/instrumentation/slip-skid-ball/indicated-slip-skid\""
#define TURN_RATE "\"/instrumentation/turn-indicator/indicated-turn-rate\""
#define SPEED_FPM "\"/instrumentation/vertical-speed-indicator/indicated-speed-fpm\""
#define AILERON "\"/controls/flight/aileron\""
#define ELEVATOR "\"/controls/flight/elevator\""
#define RUDDER "\"/controls/flight/rudder\""
#define FLAPS "\"/controls/flight/flaps\""
#define THROTTLE "\"/controls/engines/engine/throttle\""
#define RPM "\"/engines/engine/rpm\""

//linux
/*
#define INDICATE_SPD "/instrumentation/airspeed-indicator/indicated-speed-kt"
#define INDICATE_ALT "/instrumentation/altimeter/indicated-altitude-ft"
#define PRESSURE_ALT "/instrumentation/altimeter/pressure-alt-ft"
#define PITCH_DEG "/instrumentation/attitude-indicator/indicated-pitch-deg"
#define ROLL_DEG "/instrumentation/attitude-indicator/indicated-roll-deg"
#define IN_PITCH_DEG "/instrumentation/attitude-indicator/internal-pitch-deg"
#define IN_ROLL_DEG "/instrumentation/attitude-indicator/internal-roll-deg"
#define ENC_INDICATE_ALT "/instrumentation/encoder/indicated-altitude-ft"
#define ENC_PRESURE_ALT "/instrumentation/encoder/pressure-alt-ft"
#define GPS_ALT "/instrumentation/gps/indicated-altitude-ft"
#define GPS_GRND_SPD "/instrumentation/gps/indicated-ground-speed-kt"
#define GPS_VERTICAL_SPD "/instrumentation/gps/indicated-vertical-speed"
#define HEAD_DEG "/instrumentation/heading-indicator/indicated-heading-deg"
#define CMPS_HEAD_DEG "/instrumentation/magnetic-compass/indicated-heading-deg"
#define SLIP_SKID "/instrumentation/slip-skid-ball/indicated-slip-skid"
#define TURN_RATE "/instrumentation/turn-indicator/indicated-turn-rate"
#define SPEED_FPM "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"
#define AILERON "/controls/flight/aileron"
#define ELEVATOR "/controls/flight/elevator"
#define RUDDER "/controls/flight/rudder"
#define FLAPS "/controls/flight/flaps"
#define THROTTLE "/controls/engines/engine/throttle"
#define RPM "/engines/engine/rpm"
*/
#define XML_AMOUNT_VARS 23
using namespace std;

class DataReaderClient {
private:
    VarManager* _varManager;
    bool stop;
public:
    struct MyParams {
        string ip;
        int port;
        DataReaderClient *data;
    };

    DataReaderClient(VarManager *varManager){
        this->_varManager = varManager;
        this->stop = false;
    }
    void ConnectClient(string ip, int port);

    void UpdateSimulator(int sockfd);

    static void* thread_func(void* arg);

    void needToStop();
};


#endif //PROJECT_DATAREADERCLIENT_H
