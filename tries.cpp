#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "Tokenizer.h"

using namespace std;


void analyze(string s);

int asd() {

    string s;// = "var six=6 + seven ";

    s = "(x==18/2 + 3) || (breaks == 3+9)";
    analyze(s);

}

void analyze(string s) {
    Tokenizer r;
    r.SetShuntingYard();
    cout << s << endl;
    vector<Token> result = r.Lex(s);
    vector<Token>::iterator it;
    for (it = result.begin(); it != result.end(); ++it) {
        (*it).Print();
    }
    cout << endl;
}





