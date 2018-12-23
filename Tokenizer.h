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

class Tokenizer {

    list<Token> valid_tokens;

    Token GetToken(const string &value) {
        for (Token t : valid_tokens) {
            if (value == t.get_value()) {
                return t;
            }
        }
        if (IsNumber(value)) {
            return Token(NUM, value, 0, "", "");
        }
        return Token(STR, value, 0, "", "");
    }

    bool IsNumber(const string &value) {
        bool result = true;
        for (char c : value) {
            if (c < 48 || c > 57) {
                result = false;
                break;
            }
        }
        return result;
    }

    /**
 * this for is taking each valid token and check if the current
 * location in s, starts with this token value, and after the token
 * value, there is a space
 * function inline so there wont be needed to substr each iteration
 */
    bool IsToken(const PacketAnalyzer &pa, const Token &t) {
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

    /**
     * found token t in current state of packet analyzer,
     * procced with token analyze specifications.
     */
    void DoTokenSpecification(PacketAnalyzer &pa, const Token &t) {
        if (t.get_type() == SKIP) {
            /**
             * add all chars of skip token but without the last,
             * the last will be added anyway after the loop
             */
            const string &token = t.get_value();
            for (int i = 0; i < token.length(); ++i) {
                pa.current_value += token[i];
                pa.index++;
            }
        }

        else {
            if (!pa.current_value.empty()) {
                pa.new_tokens.push_back(GetToken(pa.current_value));
                pa.current_value.clear();
            }
            if (t.get_type() != DELIMITER) {
                pa.new_tokens.push_back(t);
            }
            pa.index += t.get_value().length();
        }

    }

    void RemoveWhiteSpace(PacketAnalyzer &pa) {
        string after_removal;
        for (char c : pa.line) {
            if (c != SPACE)
                after_removal += c;
        }
        pa.line = after_removal;
    }

public:

    Tokenizer() {}

    vector<Token> Lex(string str) {

        PacketAnalyzer pa;
        pa.line = std::move(str);
        pa.index = 0;

        RemoveWhiteSpace(pa);

        while (pa.index < pa.line.length()) {

            bool found_match = false;
            for (const Token &t : valid_tokens) {

                if (IsToken(pa, t)) {
                    found_match = true;
                }

                if (found_match) {
                    DoTokenSpecification(pa, t);
                    break;
                }
            }

            if (!found_match) {
                pa.current_value += pa.line[pa.index];
                pa.index++;
            }
        }

        if (!pa.current_value.empty()) {
            pa.new_tokens.push_back(GetToken(pa.current_value));
        }

        return pa.new_tokens;
    }

    void SetCommandTokenizer() {
        valid_tokens.push_back(Token(LCB, "{", 0, "", ""));
        valid_tokens.push_back(Token(RCB, "}", 0, "", ""));
        valid_tokens.push_back(Token(SKIP, "==", 0, "", ""));
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

    void SetShuntingYard() {
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
};


#endif
