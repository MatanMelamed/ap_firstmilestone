#ifndef TRY_COMMAND_H
#define TRY_COMMAND_H

#include <string>
using namespace std;

class Command{
public:
    virtual int doCommand(string * tokens,int index)=0;
};

#endif
