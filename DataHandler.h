#ifndef AP_FIRSTMILESTONE_DATAHANDLER_H
#define AP_FIRSTMILESTONE_DATAHANDLER_H


#include <vector>

using namespace std;

class DataHandler {
    vector<string> *_lexedLine;
    int index;

public:

    DataHandler() {}

    void SetData(vector<string> *newLine) {
        if (this->_lexedLine != nullptr) {
            delete this->_lexedLine;
        }
        this->_lexedLine = newLine;
        this->index = 0;
    }

    string GetCurrentString() {
        return (*this->_lexedLine)[this->index];
    }

    bool hasMoreStrings() {
        return this->_lexedLine->size() <= this->index;
    }

    string Advance(int steps) {
        this->index += steps;
    }
};


#endif //AP_FIRSTMILESTONE_DATAHANDLER_H
