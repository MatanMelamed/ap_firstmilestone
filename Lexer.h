#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "ExpressionManager.h"
#include "DataHandler.h"
#include <fstream>
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


    vector<Token> *Split(const string &line);

    void CommandLineLexer();

    void LoadFile();

    void FileLexer();

public:

    Lexer(DataHandler *dataHandler, const string &target) {
        this->_dataHandler = dataHandler;
        this->_target = target;
        this->_tokenizer.SetCommandTokenizer();
    }

    void Interpret();
};


#endif
