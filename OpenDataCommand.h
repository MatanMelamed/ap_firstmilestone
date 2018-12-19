#ifndef TRY_OPENDATACOMMAND_H
#define TRY_OPENDATACOMMAND_H

#include "Command.h"
#include "CommandFactory.h"

#define SER_EXIST_ERR "Server already exists!"

class OpenDataCommand : public Command {

    bool _called_already;
    CommandFactory *_factory;

public:

    explicit OpenDataCommand(CommandFactory *factory) {
        _called_already = false;
        _factory = factory;
    };

    int doCommand(string *tokens, int index) override;

};



#endif
