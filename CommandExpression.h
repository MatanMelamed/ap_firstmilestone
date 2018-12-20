
#ifndef PROJECT_COMMANDEXPRESSION_H
#define PROJECT_COMMANDEXPRESSION_H

#include "Command.h"
#include "Expression.h"

class CommandExpression : public Expression {

    Command *_command;
public:
    CommandExpression(Command *command) {
        this->_command = command;
    }

    void Calculate() override {
        _command->doCommand();
    }
};

#endif
