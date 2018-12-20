#ifndef AP_FIRSTMILESTONE_DATAHANDLER_H
#define AP_FIRSTMILESTONE_DATAHANDLER_H

#define INDEX_OFFSET_ERR "The offset is not valid."

#include <vector>

using namespace std;

class DataHandler {
    vector<string> *_lexedLine;
    int index;

public:

    DataHandler() {
        this->_lexedLine = NULL;
    }

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
        return this->_lexedLine->size() > this->index;
    }

    int GetIndex() {
        return this->index;
    }

    string GetStringInOffSet(int offset) {
        int wanted_index = this->index + offset;
        if (0 <= wanted_index && wanted_index < this->_lexedLine->size()) {
            return (*this->_lexedLine)[wanted_index];
        }
        return INDEX_OFFSET_ERR;
    }

    void Advance(int steps) {
        this->index += steps;
    }
};


#endif
