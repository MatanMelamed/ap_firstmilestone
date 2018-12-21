#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

enum type {
    CMD,
    SKIP,
    STR,
    DELIMITER,
    LCB, //Left Curly Brace
    RCB, //Right Curly Brace
    MATH,
    NUM,
    BOOL,
    ERR
};



class Token {

    type _type;
    string _value;
    int _priority;
    string _must_be_after;
    string _cant_be_after;

    map<int, string> type_converter = {{0, "CMD"},
                                       {1, "SKIP"},
                                       {2, "STR"},
                                       {3, "DELIMITER"},
                                       {4, "LCB"},
                                       {5, "RCB"},
                                       {6, "MATH"},
                                       {7, "NUM"},
                                       {8, "BOOL"},
                                       {9, "ERR"}};

public:

    Token() {}

    Token(type type, const string &value, int priority, string must_kriptonite,
          string cant_kriptonite) {
        this->_type = type;
        this->_value = value;
        this->_priority = priority;
        this->_must_be_after = must_kriptonite;
        this->_cant_be_after = cant_kriptonite;
    }

    type get_type() const {
        return _type;
    }

    const string &get_value() const {
        return _value;
    }

    int getPriority() const {
        return _priority;
    }

    bool isValidAfterToken(char check) const {
        bool result = true;

        if (!_must_be_after.empty()) {
            for (char c : _must_be_after) {
                if (check == c) {
                    result = true;
                    break;
                }
            }
        }

        else if (!_cant_be_after.empty()) {
            result = true;
            for (char c: _cant_be_after) {
                if (check == c) {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    void Print() {
        cout << "Type: " << type_converter.at(_type) << " ,";
        cout << "Value: " << _value << " ,";
        cout << "Priority: " << _priority << endl;
    }
};

#endif
