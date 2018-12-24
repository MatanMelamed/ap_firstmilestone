#include <utility>

#ifndef PROJECT_TOKENIZER_H
#define PROJECT_TOKENIZER_H

#include "Token.h"
#include <vector>
#include <list>

#define SPACE ' '

using namespace std;

struct PacketAnalyzer {
    string line;
    vector<Token> new_tokens;
    string current_value;
    int index = 0;
};

/***
 * this class responsible on dividing a string to vector of tokens.
 * all valid token are set in Set functions before run.
 * can add token behavior at DoTokenSpec function.
 * if merge expression bool is true, the after the split, the object merges all
 * the expressions into tokens of strings and commands,
 * the rules upon merging tokens or seperating them are in
 * MergeExpressionToOneString.
 * separating is done but this logic and sequence of tokens that is marked as
 * split, and these sequence populates in PopulateSplitSequences.
 */
class Tokenizer {

    list<Token> valid_tokens;
    bool _mergeExpressions;

    Token GetToken(const string &value);

    bool IsNumber(const string &value);

    /**
 * this for is taking each valid token and check if the current
 * location in s, starts with this token value, and after the token
 * value, there is a space
 * function inline so there wont be needed to substr each iteration
 */
    bool IsToken(const PacketAnalyzer &pa, const Token &t);

    /**
     * found token t in current state of packet analyzer,
     * procced with token analyze specifications.
     */
    void DoTokenSpecification(PacketAnalyzer &pa, const Token &t);

    void AnalyzePacket(PacketAnalyzer &pa);

public:

    Tokenizer() { _mergeExpressions = false; }

    vector<Token> Lex(string str);

    void PopulateSplitSequences(list<vector<Token>> &skipSequences);

    vector<Token> MergeExpressionToStrings(PacketAnalyzer &pa);

    void PushSumAsToken(vector<Token> &afterMerge, string &tokenSum);

    void SetCommandTokenizer();

    void SetShuntingYard();
};

#endif