#include <utility>

#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

enum TokenType {
    CMD,
    SP,
    WORD,
    DELIMITER,
    LCB, //Left Curly Brace
    RCB, //Right Curly Brace
    MATH,
    NUM,
    BOOL,
    ERR,
    LRB,
    RRB,
    STR,
};


class Token {

    TokenType _type;
    string _value;
    int _priority;
    string _must_be_after;
    string _cant_be_after;

    map<int, string> type_converter = {{0,  "CMD"},
                                       {1,  "SP"},
                                       {2,  "WORD"},
                                       {3,  "DELIMITER"},
                                       {4,  "LCB"},
                                       {5,  "RCB"},
                                       {6,  "MATH"},
                                       {7,  "NUM"},
                                       {8,  "BOOL"},
                                       {9,  "ERR"},
                                       {10, "LRB"},
                                       {11, "RRB"},
                                       {12, "STR"}};

public:

    Token() {}

    Token(TokenType type, const string &value, int priority,
          string must_kriptonite,
          string cant_kriptonite) {
        this->_type = type;
        this->_value = value;
        this->_priority = priority;
        this->_must_be_after = std::move(must_kriptonite);
        this->_cant_be_after = std::move(cant_kriptonite);
    }

    TokenType get_type() const {
        return _type;
    }

    const string &get_value() const {
        return _value;
    }

    int getPriority() const {
        return _priority;
    }

    bool isValidAfterToken(char check) const;

    void Print() {
        cout << "Type: " << type_converter.at(_type) << " ,";
        cout << "Value: " << _value << " ,";
        cout << "len: " << _value.length() << ", ";
        cout << "Priority: " << _priority << endl;
    }
};

#endif