#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H


#include "DataHandler.h"

class Command {

protected:
    DataHandler *_dataHandler;
public:

    //must advance handler by parameters used
    virtual void doCommand();

    void SetDataHandler(DataHandler *dataHandler) {
        this->_dataHandler = dataHandler;
    }

};

#endif
