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
    SleepCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {}

    void doCommand() override {
        _dataHandler->Advance(1);
        Token sleepTime = _dataHandler->GetCurrentToken();
        this_thread::sleep_for(chrono::milliseconds((unsigned int)stoi
                (sleepTime.get_value())));
        _dataHandler->Advance(1);
    }
};
#endif
