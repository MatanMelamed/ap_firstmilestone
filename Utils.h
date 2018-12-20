#ifndef TRY_UTILS_H
#define TRY_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;


vector<string> Split(const string &s, const string &splitters) {

    vector<string> tokens;
    string token;

    int index = 0;
    bool skip_char;
    while (index < s.length()) {
        skip_char = false;
        for (char delimiter : splitters) {
            if (s[index] == delimiter) {
                tokens.push_back(token);
                token.clear();
                index++;
                skip_char = true;
                continue;
            }
        }
        if (!skip_char) {
            token += s[index];
            index++;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

template<typename T>
void pop(map<string, T> *m) {
    string delimiter ="\n";
    string all;
    ifstream file("paths.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            all += line + delimiter;
        }
        file.close();
    }
    vector<string> paths = Split(all, delimiter);
    for (vector<string>::const_iterator i = paths.begin();
         i != paths.end(); ++i) {
        (*m)[(*i)];
    }
}


#endif
