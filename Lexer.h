#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "ExpressionManager.h"
#include "DataHandler.h"
#include <fstream>
#include "Utils.h"
#include "Tokenizer.h"

#define NOT_FILE "not a file."
#define CONSOLE_PREFIX ">> "

using namespace std;

class Lexer {

    DataHandler *_dataHandler;
    Tokenizer _tokenizer;

    vector<string> _lines;
    int _lineNumber;
    string _target;


    vector<Token> *Split(const string &line) {
        auto *result = new vector<Token>;

        (*result) = _tokenizer.Lex(line);

        return result;
    }

    void CommandLineLexer() {
        string line;
        cout << CONSOLE_PREFIX;
        getline(cin, line);
        if (!line.empty()) {
            vector<Token> *splitted = Split(line);
            this->_dataHandler->SetNewLine(splitted);
        }
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

        if ((int) this->_lines.size() <= this->_lineNumber) {
            this->_target = NOT_FILE;
            CommandLineLexer();
        } else {
            string line = this->_lines[this->_lineNumber];
            this->_lineNumber++;

            vector<Token> *splitted = Split(line);

            this->_dataHandler->SetNewLine(splitted);
        }
    }

public:

    Lexer(DataHandler *dataHandler, const string &target) {
        this->_dataHandler = dataHandler;
        this->_target = target;
        this->_tokenizer.SetCommandTokenizer();
    }

    void Interpret() {
        if (_dataHandler->GetState() != RUN) {
            if (this->_target == NOT_FILE) {
                CommandLineLexer();
            } else {
                FileLexer();
            }
        }
    }
};


#endif
