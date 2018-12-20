#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "ExpressionManager.h"
#include "DataHandler.h"
#include <fstream>
#include "Utils.h"

#define NOT_FILE "not a file."
#define CONSOLE_PREFIX ">> "

using namespace std;

vector<string> *VarSpliter(string line);


class Lexer {

    ExpressionManager *_expressionManager;
    DataHandler *_dataHandler;

    vector<string> _lines;
    int _lineNumber;
    string _target;


    vector<string> *Split(const string &line) {
        auto *result = new vector<string>;

        result = VarSpliter(line);

        // delete all white spaces and separate by commands and ','


        return result;
    }

    void CommandLineLexer() {
        string line;
        cout << CONSOLE_PREFIX;
        getline(cin, line);
        //cin >> line;

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
            this->_lineNumber = 0;
        }

        if ((int) this->_lines.size() >= this->_lineNumber) {
            this->_target = NOT_FILE;
            CommandLineLexer();
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
        }
        else {
            FileLexer();
        }
    }
};

vector<string> *VarSpliter(string line) {
    auto *splitted = new vector<string>;
    int space_index;
    int index = line.find("var");
    line = line.substr(index, line.length());
    string st = line.substr(0, line.find(" "));
    splitted->push_back(st);
    space_index = line.find(' ');
    line = line.substr(space_index, line.length());
    while (line[0] == ' ') {
        line = line.substr(1, line.length());
    }
    space_index = line.find(' ');
    st = line.substr(0, space_index);
    splitted->push_back(st);
    line = line.substr(space_index, line.length());
    while (line[0] == ' ' && line[0] != '=') {
        line = line.substr(1, line.length());
    }
    st = line[0];
    splitted->push_back(st);
    space_index = line.find(' ');
    line = line.substr(space_index, line.length());
    while (line[0] == ' ') {
        line = line.substr(1, line.length());
    }
    st = line.substr(0, 4);
    if (st == "bind") {
        splitted->push_back(st);
        line = line.substr(5, line.length());
        while (line[0] == ' ') {
            line.substr(1, line.length());
        }
        splitted->push_back(line.substr(5, line.length()));
    }
    else {
        splitted->push_back(line);
    }
    return splitted;
}


#endif
