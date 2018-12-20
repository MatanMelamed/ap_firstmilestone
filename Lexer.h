#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "ExpressionManager.h"
#include "DataHandler.h"
#include <fstream>

#define NOT_FILE "not a file."
#define CONSOLE_PREFIX ">> "

using namespace std;

class Lexer {

    ExpressionManager *_expressionManager;
    DataHandler *_dataHandler;

    vector<string> _lines;
    int _lineNumber;
    string _target;


    vector<string> *Split(const string &line) {
        auto *result = new vector<string>;

        // delete all white spaces and separate by commands and ','

        return result;
    }

    void CommandLineLexer() {
        string line;
        cout << CONSOLE_PREFIX;
        cin >> line;

        vector<string> *splitted = Split(line);

        this->_dataHandler->SetData(splitted);
    }

    void LoadFile() {
        ifstream file(this->_target);
        if (file.is_open()) {
            string newLine;
            while (getline(file, newLine)) {
                this->_lines.push_back(newLine);
            }
            file.close();
        }
    }

    void FileLexer() {
        if (this->_lines.empty()) {
            LoadFile();
            this->_lineNumber = (int) this->_lines.size();
        }

        string line = this->_lines[this->_lineNumber];
        this->_lineNumber++;

        vector<string> *splitted = Split(line);

        this->_dataHandler->SetData(splitted);
    }

public:

    Lexer() {};

    Lexer(DataHandler *dataHandler, ExpressionManager *expressionManager,
          const string &target) {
        this->_dataHandler = dataHandler;
        this->_expressionManager = expressionManager;
        this->_target = target;
    }

    string Interpret() {
        if (this->_target == NOT_FILE) {
            CommandLineLexer();
        } else {
            FileLexer();
        }
    }
};

#endif
