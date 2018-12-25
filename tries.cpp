#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "Tokenizer.h"

using namespace std;


void analyze(string s);

int asd() {

    string s = "\"sdsds\"";
    cout << s;
    s = (s.substr(0, s.length() - 1)).substr(1, s.length() - 1);

    cout << s;
    return 0;


}

/**
 *     list<vector<Token>> skipSequences;
    skipSequences.push_back(arr);
    list<vector<Token>>::iterator it;

    for (it = skipSequences.begin(); it != skipSequences.end(); ++it) {
        cout << (*it)[0].get_value() << (*it)[1].get_value() << endl;
    }
 * @param s
 */

void analyze(string s) {
    Tokenizer r;
    r.SetCommandTokenizer();
    cout << s << endl;
    vector<Token> result = r.Lex(s);
    vector<Token>::iterator it;
    for (it = result.begin(); it != result.end(); ++it) {
        (*it).Print();
    }
    cout << endl;
}





