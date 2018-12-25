#include "Utils.h"

/**
 * receives a string of doubles separated by ','.
 * returns vector of doubles with these values.
 */
vector<double> StringSeparator(string input) {

    vector<double> result;
    string currentValue;
    int index = 0;

    while (index < input.length()) {
        if (input[index] == ',') {
            if (!currentValue.empty()) {
                result.push_back(stod(currentValue));
                currentValue.clear();
            }
        } else {
            currentValue += input[index];
        }
        index++;
    }

    if (!currentValue.empty()) {
        result.push_back(stod(currentValue));
    }

    return result;
}

bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers) {
    bool hasNewLine = false;

    if (!leftovers.empty()) {
        int index = 0;
        while (index < leftovers.length()) {
            if (leftovers[index] != '\n') {
                current_string += leftovers[index];
            } else {
                hasNewLine = true;
                break;
            }
            index++;
        }
        if(index == leftovers.length()){
            leftovers.clear();
        } else{
            leftovers = leftovers.substr(index + 1, leftovers.length() - index - 1);
        }
    }

    return hasNewLine;
}

/***
 * receivces a buffer - target string to populate with all chars from,
 * firstly leftovers if there are - in string leftover, then wll chars from
 * buffer.
 *
 */
bool AddToCurrent(const string &buffer, string &current_string,
                  string &leftovers) {
    int index = 0;
    bool hasNewLine = UpdateCurrentFromLeftOvers(current_string, leftovers);

    while (index < buffer.length()) {
        if (buffer[index] == '\n') {
            if (hasNewLine) {
                leftovers += buffer[index];
            } else {
                hasNewLine = true;
            }
        } else if (hasNewLine) {
            leftovers += buffer[index];
        } else {
            current_string += buffer[index];
        }
        index++;
    }

    return hasNewLine;
}

