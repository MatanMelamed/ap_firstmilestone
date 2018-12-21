//
// Created by tomme on 20/12/2018.
//

#ifndef PROJECT_SLEEPCOMMAND_H
#define PROJECT_SLEEPCOMMAND_H


#define ONE 1
#define TWO 2

#include "Command.h"
#include <chrono>
#include <thread>
#include <stdexcept>
using namespace std;

class SleepCommand: public Command {

public:
    SleepCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    double doCommand() {
        _dataHandler->Advance(1);
        string sleepTime = _dataHandler->GetCurrentString();
        this_thread::sleep_for(chrono::milliseconds((unsigned int)stoi
                (sleepTime)));
        _dataHandler->Advance(1);
        return 0;
    }
};
#endif //PROJECT_SLEEPCOMMAND_H
