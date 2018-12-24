#include "Tokenizer.h"


Token Tokenizer::GetToken(const string &value) {
    for (Token t : valid_tokens) {
        if (value == t.get_value()) {
            return t;
        }
    }
    if (IsNumber(value)) {
        return Token(NUM, value, 0, "", "");
    }
    return Token(WORD, value, 0, "", "");
}

bool Tokenizer::IsNumber(const string &value) {
    bool result = true;
    for (char c : value) {
        if (c < 48 || c > 57) {
            result = false;
            break;
        }
    }
    return result;
}

bool Tokenizer::IsToken(const PacketAnalyzer &pa, const Token &t) {
    bool result = true;

    // cant fit the token in the rest of s.
    if (pa.line.length() - pa.index < t.get_value().length()) {
        return !result;
    }

    /**
     * can fit token in s and more, but there is no space after.
     * commands must have a space after them!
     */
    if (pa.line.length() - pa.index > t.get_value().length() &&
        !t.isValidAfterToken(pa.line[pa.index + t.get_value().length()])) {
        return !result;
    }

    //check chars equality - char by char
    for (int j = 0; j < t.get_value().length(); ++j) {
        if (pa.line[pa.index + j] != t.get_value()[j]) {
            result = false;
            break;
        }
    }
    return result;
}

void Tokenizer::DoTokenSpecification(PacketAnalyzer &pa, const Token &t) {
    if (!pa.current_value.empty()) {
        pa.new_tokens.push_back(GetToken(pa.current_value));
        pa.current_value.clear();
    }
    /**
     * when merging several tokens after the split process,
     * it should keep the delimiters tokens too,
     * else, dont keep the delimiters
     * never keep space tokens.
     */
    if (t.get_type() == STR) {
        while (pa.index < pa.line.length()) {
            pa.current_value += pa.line[pa.index];
            pa.index++;
        }
        pa.new_tokens.emplace_back(STR, pa.current_value, 0, "", "");
        pa.current_value.empty();
        return;
    } else if ((t.get_type() != DELIMITER || _mergeExpressions) &&
               (t.get_type() != SP)) {
        pa.new_tokens.push_back(t);
    }
    pa.index += t.get_value().length();
}

void Tokenizer::AnalyzePacket(PacketAnalyzer &pa) {
    while (pa.index < pa.line.length()) {

        bool found_match = false;
        for (const Token &t : valid_tokens) {

            if (IsToken(pa, t)) {
                found_match = true;
                DoTokenSpecification(pa, t);
                break;
            }
        }

        if (!found_match && (pa.index < pa.line.length())) {
            pa.current_value += pa.line[pa.index];
            pa.index++;
        }
    }

    if (!pa.current_value.empty()) {
        pa.new_tokens.push_back(GetToken(pa.current_value));
    }
}

vector<Token> Tokenizer::Lex(string str) {
    PacketAnalyzer pa;
    pa.line = std::move(str);
    pa.index = 0;

    AnalyzePacket(pa);

    if (_mergeExpressions) {
        pa.new_tokens = MergeExpressionToStrings(pa);
    }
    return pa.new_tokens;
}

void Tokenizer::PopulateSplitSequences(list<vector<Token>> &skipSequences) {
    skipSequences.push_back({Token(RRB, ")", 0, "", ""),
                             Token(LRB, "(", 0, "", "")});

    skipSequences.push_back({Token(NUM, "1", 0, "", ""),
                             Token(LRB, "(", 0, "", "")});

    skipSequences.push_back({Token(WORD, "x", 0, "", ""),
                             Token(LRB, "(", 0, "", "")});

    skipSequences.push_back({Token(RRB, ")", 0, "", ""),
                             Token(NUM, "1", 0, "", "")});

    skipSequences.push_back({Token(RRB, ")", 0, "", ""),
                             Token(WORD, "X", 0, "", "")});

    skipSequences.push_back({Token(NUM, "1", 0, "", ""),
                             Token(NUM, "1", 0, "", "")});

    skipSequences.push_back({Token(NUM, "1", 0, "", ""),
                             Token(WORD, "x", 0, "", "")});

    skipSequences.push_back({Token(WORD, "x", 0, "", ""),
                             Token(NUM, "1", 0, "", "")});

    skipSequences.push_back({Token(WORD, "x", 0, "", ""),
                             Token(WORD, "X", 0, "", "")});
}

vector<Token> Tokenizer::MergeExpressionToStrings(PacketAnalyzer &pa) {
    vector<Token> afterMerge;
    string tokenSum;

    list<vector<Token>> splitSequences;

    PopulateSplitSequences(splitSequences);


    for (int i = 0; i < pa.new_tokens.size(); ++i) {
        Token *currentToken = &pa.new_tokens[i];

        // for tokens that do not need to be merged.
        if (currentToken->get_type() == CMD ||
            currentToken->get_type() == LCB) {
            PushSumAsToken(afterMerge, tokenSum);
            afterMerge.push_back(*currentToken);
            continue;
        } else if (currentToken->get_type() == DELIMITER) {
            //for tokens that should split and not be accounted for.
            PushSumAsToken(afterMerge, tokenSum);
            continue;
        } else if (i == 0) {
            //do not need to check for pairs, has no previous token.
            tokenSum += currentToken->get_value();
            continue;
        }
        /**
         * for a two token sequence that should be splitted.
         * like "..)(..","...10 10...", "...variable 10..." etc.
         * to add more sequence simply add them to the list in
         * PopulateSkipSequences.
         */
        bool found_pair = false;

        list<vector<Token> >::iterator it;
        for (it = splitSequences.begin();
             it != splitSequences.end(); ++it) {
            if (currentToken->get_type() == (*it)[1].get_type()
                &&
                (pa.new_tokens)[i - 1].get_type() == (*it)[0].get_type()) {
                PushSumAsToken(afterMerge, tokenSum);
                tokenSum += currentToken->get_value();
                found_pair = true;
                continue;
            }
        }
        if (!found_pair) {
            tokenSum += currentToken->get_value();
        }
    }

    PushSumAsToken(afterMerge, tokenSum);

    return afterMerge;
}

void Tokenizer::PushSumAsToken(vector<Token> &afterMerge, string &tokenSum) {
    if (!tokenSum.empty()) {
        afterMerge.push_back(Token(WORD, tokenSum, 0, "", ""));
        tokenSum.clear();
    }
}

void Tokenizer::SetCommandTokenizer() {
    _mergeExpressions = true;
    valid_tokens.push_back(Token(SP, " ", 0, "", ""));
    valid_tokens.push_back(Token(STR, "\"", 0, "", ""));
    valid_tokens.push_back(Token(LRB, "(", 0, "", ""));
    valid_tokens.push_back(Token(RRB, ")", 0, "", ""));
    valid_tokens.push_back(Token(MATH, "+", 4, "", ""));
    valid_tokens.push_back(Token(MATH, "-", 4, "", ""));
    valid_tokens.push_back(Token(MATH, "/", 5, "", ""));
    valid_tokens.push_back(Token(MATH, "*", 5, "", ""));
    valid_tokens.push_back(Token(BOOL, ">", 3, "", "="));
    valid_tokens.push_back(Token(BOOL, "<", 3, "", "="));
    valid_tokens.push_back(Token(BOOL, ">=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "<=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "==", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "!=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "&&", 2, "", ""));
    valid_tokens.push_back(Token(BOOL, "||", 1, "", ""));
    valid_tokens.push_back(Token(LCB, "{", 0, "", ""));
    valid_tokens.push_back(Token(RCB, "}", 0, "", ""));
    valid_tokens.push_back(Token(DELIMITER, ",", 0, "", ""));
    valid_tokens.push_back(Token(CMD, "=", 0, "", "="));
    valid_tokens.push_back(Token(CMD, "bind", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "print", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "connect", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "openDataServer", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "var", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "while", 0, " ", ""));
    valid_tokens.push_back(Token(CMD, "if", 0, " ", ""));
}

void Tokenizer::SetShuntingYard() {
    valid_tokens.push_back(Token(MATH, "(", 0, "", ""));
    valid_tokens.push_back(Token(MATH, ")", 0, "", ""));
    valid_tokens.push_back(Token(MATH, "+", 4, "", ""));
    valid_tokens.push_back(Token(MATH, "-", 4, "", ""));
    valid_tokens.push_back(Token(MATH, "/", 5, "", ""));
    valid_tokens.push_back(Token(MATH, "*", 5, "", ""));
    valid_tokens.push_back(Token(BOOL, ">", 3, "", "="));
    valid_tokens.push_back(Token(BOOL, "<", 3, "", "="));
    valid_tokens.push_back(Token(BOOL, ">=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "<=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "==", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "!=", 3, "", ""));
    valid_tokens.push_back(Token(BOOL, "&&", 2, "", ""));
    valid_tokens.push_back(Token(BOOL, "||", 1, "", ""));
}
