#ifndef AP_FIRSTMILESTONE_DATAHANDLER_H
#define AP_FIRSTMILESTONE_DATAHANDLER_H

#include <vector>
#include "Tokenizer.h"

#define NEXT 1
#define MINUS_ONE -1
#define ONE 1
#define TWO 2
#define INDEX_OFFSET_ERR Token(ERR,"offset out of range",0,"","");

using namespace std;

class DataHandler {
    vector<vector<Token> *> _all_lines;
    int _currentLineIndex;
    int _currentTokenIndex;

public:

    DataHandler() {
        this->_currentLineIndex = -1;
    }

    void SetNewLine(vector<Token> *newLine) {

        this->_all_lines.push_back(newLine);
        this->_currentLineIndex++;
        this->_currentTokenIndex = 0;
    }

    Token GetCurrentToken() {
        vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
        return (*current_line)[this->_currentTokenIndex];
    }

    bool hasMoreTokens() {
        vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
        return current_line->size() > this->_currentTokenIndex;
    }

    int GetIndexOfTokenInLine() {
        return this->_currentTokenIndex;
    }

    Token GetTokenInOffSet(int offset) {
        int wanted_index = this->_currentTokenIndex + offset;
        vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
        if (0 <= wanted_index && wanted_index < current_line->size()) {
            return (*current_line)[wanted_index];
        }
        return INDEX_OFFSET_ERR
    }

    void Advance(int steps) {
        this->_currentTokenIndex += steps;
    }
};


#endif
