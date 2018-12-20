#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstring>
#include "Expression.h"
#include "Minus.h"
#include "Plus.h"
#include "Div.h"
#include "Number.h"
#include "Mult.h"
#include "General_Manager.h"
using namespace std;

vector<string> lexer(string line);
void parser(vector<string> textInArray);
vector<string> OpenDataSpliter(string line);
vector<string> ConnectSpliter(string line);
vector<string> WhileSpliter(string line);
vector<string> IfSpliter(string line);
vector<string> VarSpliter(string line);
vector<string> EqualSpliter(string line);
vector<string> SleepSpliter(string line);
vector<string> PrintSpliter(string line);

int main() {
    std::cout << "Hello, World!" << std::endl;
    vector<string> wholeText;
    ifstream ifs;
    ifs.open("commands.txt");
    if(ifs.is_open()) {
        string line;
        while(getline(ifs,line)) {
            vector<string> cut_line =lexer(line);
            for (string cut : cut_line) {
                wholeText.push_back(cut);
            }
        }
    }
    Expression *e = new Mult(new Number(5),new Plus(new Number(3),
            new Number(3)));
    cout<<e->calculate()<<endl;
    parser(wholeText);
    return 0;
}

vector<string> lexer(string line){
    vector<string> array;

    if(strstr(line.c_str(),"openDataServer")) {
        array = OpenDataSpliter(line);
    }
    if(strstr(line.c_str(),"while")){
        array = WhileSpliter(line);
    }
    if(strstr(line.c_str(),"print")) {
        array = PrintSpliter(line);
    }
    if(strstr(line.c_str(),"sleep")) {
        array = SleepSpliter(line);
    }
    if(strstr(line.c_str(),"if")) {
        array = IfSpliter(line);
    }
    if(strstr(line.c_str(),"var")){
        array = VarSpliter(line);
    }
    else{
        if(strstr(line.c_str(),"=")) {
            array = EqualSpliter(line);
        }
    }
    if(line=="}"){
        array.push_back(line);
    }
    return array;
}

void parser(vector<string> textInArray){
    General_Manager* gm = new General_Manager();
    int index = 0;
    while(index<textInArray.size()){
        Expression* exp = gm->get(textInArray[index]);
        if(exp!=NULL){
            index+=exp->calculate();
        } else {
            index++;
        }
    }
}


vector<string> OpenDataSpliter(string line){
    vector<string> splitted;
    int space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    line= line.substr(0,line.length()-1);
    string st="";
    while(line[0]!=' '){
        st = st+line[0];
        line = line.substr(1, line.length());
    }
    splitted.push_back(st);
}
vector<string> ConnectSpliter(string line){
    vector<string> splitted;
}

vector<string> WhileSpliter(string line){
    vector<string> splitted;
    int space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    line= line.substr(0,line.length()-1);
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    space_index = line.find(' ');
    string st = line.substr(0,space_index);
    splitted.push_back(st);
    line = line.substr(space_index,line.length());
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    st="";
    while(line[0]!='='&&line[0]!='<'&&line[0]!='>' && line[0]!=' '){
        st = st + line[0];
        line = line.substr(1, line.length());
    }
    splitted.push_back(st);
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    st="";
    if(line[1]=='='){
        st=line.substr(0,2);
        line = line.substr(2, line.length());
    } else{
        st = line[0];
        line = line.substr(1, line.length());
    }
    splitted.push_back(st);
    while(line[0]!=' '){
        line.substr(1,line.length());
    }
    st="";
    while(line[0]!='{'){
        st = st+line[0];
        line = line.substr(1, line.length());
    }
    splitted.push_back(st);
    splitted.push_back(line);
    return splitted;
}
vector<string> IfSpliter(string line){
    vector<string> splitted;
}
vector<string> VarSpliter(string line){
    vector<string> splitted;
    int space_index;
    int index = line.find("var");
    line = line.substr(index,line.length()-1);
    string st = line.substr(0,line.find(" "));
    splitted.push_back(st);
    space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    while(line[0]==' '){
        line = line.substr(1,line.length());
    }
    space_index = line.find(' ');
    st = line.substr(0,space_index);
    splitted.push_back(st);
    line = line.substr(space_index,line.length());
    while(line[0]==' '&&line[0]!='='){
        line = line.substr(1,line.length());
    }
    st = line[0];
    splitted.push_back(st);
    space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    while(line[0]==' '){
        line = line.substr(1,line.length());
    }
    st = line.substr(0,4);
    if(st =="bind"){
        splitted.push_back(st);
        line = line.substr(5, line.length());
        while(line[0]==' '){
            line.substr(1, line.length());
        }
        splitted.push_back(line.substr(5,line.length()));
    }else {
        splitted.push_back(line);
    }
    return splitted;
}

vector<string> EqualSpliter(string line){
    vector<string> splitted;
    int space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    line = line.substr(0,line.length()-1);
    string st;
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    while(line[0]!=' ' &&line[0]!= '='){
        st = st+line[0];
        line = line.substr(1, line.length());
    }
    splitted.push_back(st);
    while(line[0]==' '&&line[0]!='='){
        line = line.substr(1,line.length());
    }
    st = line[0];
    splitted.push_back(st);
    line = line.substr(1, line.length());
    while(line[0] == ' '){
        line = line.substr(1, line.length());
    }
    splitted.push_back(line);
    return splitted;
}

vector<string> SleepSpliter(string line){
    vector<string> splitted;
    int space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    line= line.substr(0,line.length()-1);
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    space_index = line.find(' ');
    string st = line.substr(0,space_index);
    splitted.push_back(st);
    line = line.substr(space_index,line.length());
    while(line[0]!=' '){
        line = line.substr(1, line.length());
    }
    splitted.push_back(line);
    return splitted;
}
vector<string> PrintSpliter(string line){
    vector<string> splitted;
    int space_index = line.find(' ');
    line = line.substr(space_index,line.length());
    line= line.substr(0,line.length()-1);
    while(line[0]==' '){
        line = line.substr(1, line.length());
    }
    space_index = line.find(' ');
    string st = line.substr(0,space_index);
    splitted.push_back(st);
    line = line.substr(space_index,line.length());
    while(line[0]!=' '){
        line = line.substr(1, line.length());
    }
    splitted.push_back(line);
    return splitted;
}
