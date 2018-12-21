#ifndef PROJECT_SLEEPCOMMAND_H
#define PROJECT_SLEEPCOMMAND_H

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
    void doCommand() {
        _dataHandler->Advance(ONE);
        string sleepTime = _dataHandler->GetCurrentToken().get_value();
        this_thread::sleep_for(chrono::milliseconds((unsigned int)stoi
                (sleepTime)));
        _dataHandler->Advance(ONE);
    }
};
#endif