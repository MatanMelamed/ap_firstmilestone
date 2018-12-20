#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H


#include "DataHandler.h"

class Command {

protected:
    DataHandler *_dataHandler;
    VarManager *_varManager;
public:
    Command() {
        this->_dataHandler = nullptr;
        this->_varManager = nullptr;
    }

    //MUST advance handler by parameters used + 1
    virtual void doCommand() = 0;
};

#endif
