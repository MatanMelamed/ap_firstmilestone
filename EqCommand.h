//
// Created by tomme on 20/12/2018.
//

#ifndef PROJECT_EQCOMMAND_H
#define PROJECT_EQCOMMAND_H

#define MINUS_ONE -1
#define ONE 1
#define TWO 2

#include "Command.h"
using namespace std;

class EqCommand: public Command {
public:
    EqCommand(DataHandler *dataHandler, VarManager *varManager) {
        this->_varManager = varManager;
        this->_dataHandler = dataHandler;
    }

    void doCommand() override {

        this->_dataHandler->Advance(MINUS_ONE);
        string varName = this->_dataHandler->GetCurrentString();
        this->_dataHandler->Advance(TWO);


        string value = this->_dataHandler->GetCurrentString();
        if(value=="bind"){
            this->_dataHandler->Advance(ONE);
            value = this->_dataHandler->GetCurrentString();
            this->_varManager->SetPath(varName, value);
        } else {
            //change it to get Expression
            this->_varManager->SetValue(varName, stod(value));
        }

        this->_dataHandler->Advance(ONE);
    }
};

#endif //PROJECT_EQCOMMAND_H
