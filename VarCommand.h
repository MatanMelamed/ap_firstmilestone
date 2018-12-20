
#ifndef PROJECT_VARCOMMAND_H
#define PROJECT_VARCOMMAND_H

#include "Command.h"
#define STEPS 3

class VarCommand : public Command{

public:
    void doCommand() override {

        //.....

        this->_dataHandler->Advance(STEPS);
    }
};

#endif
