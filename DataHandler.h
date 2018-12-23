#ifndef AP_FIRSTMILESTONE_DATAHANDLER_H
#define AP_FIRSTMILESTONE_DATAHANDLER_H

#include <vector>
#include <stack>
#include "Tokenizer.h"

#define NEXT 1
#define START_BRACkETS_NUM 0
#define RESET_TOKEN_INDEX 0
#define RESET_LINE_INDEX -1
#define MINUS_ONE -1
#define ONE 1
#define TWO 2
#define INDEX_OFFSET_ERR Token(ERR,"offset out of range",0,"","");

using namespace std;

struct BracketPair {
    int _openLine;
    int _closeLine;
};

enum recv_state {
    READ,       // only read
    EXECUTE,    // read and execute
    RUN,        // only execute
};

/**
 * this class controls and holds the lines as vector of token for each line.
 * responsible to mark the current line and current token in line.
 * also have the responsibility to read scopes, and when running on a scope,
 * which is only when it has a valid pairs, keep track and serve the next data.
 * controls the flow with states: execute - interpreter - mark current(last)
 * line for the rest to execute and run on it.
 * read - only reading lines - when building scopes for if and while.
 * run - after finishing building the main scope - lexer won't be adding new
 * lines until the scope is finished, parser will execute the current token,
 * so keep track and redirect '}' to is opener.
 */
class DataHandler {
    vector<vector<Token> *> _all_lines;
    int _currentLineIndex;
    int _currentTokenIndex;

    recv_state _state;

    int runUntilLine;   // main scope last line - '}'
    int _openBrackets;  // number of currently unclosed brackets - in READ state
    vector<BracketPair *> _brackets;  // all brackets pairs - keep track
    stack<BracketPair *> _brackets_queue; // for building main scopes.

    int GetStartOfScope(int closeLine) {
        int openLine = closeLine;
        for (BracketPair *pair : _brackets) {
            if (pair->_closeLine == closeLine) {
                openLine = pair->_openLine;
                break;
            }
        }
        return openLine;
    }

    bool IsBracketPairExists(int startLine) {
        bool result = false;
        for (BracketPair *pair : _brackets) {
            if (pair->_openLine == startLine) {
                result = true;
                break;
            }
        }
        return result;
    }

    void AddOpenBracket(int startLine) {
        BracketPair *pair = new BracketPair;
        pair->_openLine = startLine;
        pair->_closeLine = startLine;

        _brackets.push_back(pair);
        _brackets_queue.push(pair);
        _openBrackets++;
    }

    void AddCloseBracket(int closeLine) {
        BracketPair *pair = _brackets_queue.top();
        _brackets_queue.pop();
        pair->_closeLine = closeLine;
        _openBrackets--;
    }

    void HandleEXECUTEState() {
        if (hasTokenTypeInCurrentLine(LCB)) {
            if (!IsBracketPairExists(_currentLineIndex)) {
                // start scope for the first time !
                AddOpenBracket(_currentLineIndex);
            }
        } else if (hasTokenTypeInCurrentLine(RCB)) {
            _currentLineIndex = GetStartOfScope(_currentLineIndex);
        }
    }

    bool hasTokenTypeInCurrentLine(const TokenType &type) {
        bool result = false;
        for (const Token &token : (*_all_lines[_currentLineIndex])) {
            if (token.get_type() == type) {
                result = true;
                break;
            }
        }
        return result;
    }

    void HandleREADState() {

        if (hasTokenTypeInCurrentLine(LCB)) {
            AddOpenBracket(_currentLineIndex);
        } else if (hasTokenTypeInCurrentLine(RCB)) {
            if (_openBrackets == START_BRACkETS_NUM) {
                // there are 0 open scopes
                //  exception
            } else if ((_all_lines[_currentLineIndex])->size() > 1) {
                // line has } and more than one token.
                // exception
            } else {  // there is at least one open scope and valid RCB
                AddCloseBracket(_currentLineIndex);
                if (_openBrackets == START_BRACkETS_NUM) {
                    StartRun();
                }
            }
        }

    }

    void HandleRUNState() {
        if (!hasMoreTokens()) {
            GoToNextLine();
        } else if (GetCurrentToken().get_type() == RCB) {
            _currentLineIndex = GetStartOfScope(_currentLineIndex);
        }
    }

    void HandleStates() {
        if (_state == EXECUTE) {
            HandleEXECUTEState();
        } else if (_state == READ) {
            HandleREADState();
        } else if (_state == RUN) {
            HandleRUNState();
        }
    }

public:

    DataHandler() {
        this->_currentLineIndex = RESET_LINE_INDEX;
        this->_state = EXECUTE;
        this->_openBrackets = 0;
    }

    // Getters
    Token GetCurrentToken() {
        vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
        return (*current_line)[this->_currentTokenIndex];
    }

    Token GetTokenInOffSet(int offset) {
        int wanted_index = this->_currentTokenIndex + offset;
        vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
        if (0 <= wanted_index && wanted_index < current_line->size()) {
            return (*current_line)[wanted_index];
        }
        return INDEX_OFFSET_ERR
    }

    recv_state GetState() {
        return this->_state;
    }

    int GetCurrentLineIndex() {
        return this->_currentLineIndex;
    }

    int GetLineSize() {
        return (int) _all_lines[_currentLineIndex]->size();
    }

    int GetEndOfScope(int startLine) {
        int endLine = startLine;
        for (BracketPair *pair : _brackets) {
            if (pair->_openLine == startLine) {
                endLine = pair->_closeLine;
                break;
            }
        }
        return endLine;
    }

    // functionality for data control
    void SetNewLine(vector<Token> *newLine) {
        this->_all_lines.push_back(newLine);
        this->_currentLineIndex = (int) _all_lines.size() - 1;
        this->_currentTokenIndex = RESET_TOKEN_INDEX;
        HandleStates();
    }

    void Advance(int steps) {
        _currentTokenIndex += steps;
        vector<Token> *currentLine = _all_lines[_currentLineIndex];
        if (_currentTokenIndex >= currentLine->size()) {
            // need to move to next line - if exists!
            GoToNextLine();
        }
    }

    void SetState(recv_state _state) {
        this->_state = _state;
    }

    void SetTokenIndexToEndOfLine() {
        _currentTokenIndex = (int) _all_lines[_currentLineIndex]->size();
    }

    void StartRead() {
        SetState(READ);
        SetTokenIndexToEndOfLine();
    }

    void StartRun() {
        _state = RUN;
        runUntilLine = GetEndOfScope(_currentLineIndex);
        _currentLineIndex = GetStartOfScope(runUntilLine);
        _currentTokenIndex = 0;
    }

    void StopRun() {
        _state = EXECUTE;
        Advance(GetLineSize());
    }

    void GoToNextLine() {
        if (_currentLineIndex < _all_lines.size() - 1) {
            _currentLineIndex++;
            _currentTokenIndex = 0;
            HandleStates();
        }
    }

    /**
     * is called on the first line of the scope.
     */
    void SkipCurrentScope() {
        _currentLineIndex = GetEndOfScope(_currentLineIndex);
        if (_currentLineIndex == runUntilLine) {
            StopRun();  //reached last scope end.
        } else {
            _currentLineIndex++;
            HandleStates();
        }
    }

    // Information functions
    bool hasMoreTokens() {
        if (_all_lines.size() <= _currentLineIndex) {
            return false;
        }
        return _all_lines[_currentLineIndex]->size() > _currentTokenIndex;
    }

    bool IsScopeReady(int scopeLine) {
        return _openBrackets == 0;
    }

    void printline() {
        cout << _all_lines[_currentLineIndex]->size() << endl;
    }

    string h() {
        string s;
        for (Token t : *_all_lines[_currentLineIndex]) {
            s += t.get_value() + " ";
        }
        return s;
    }
};


#endif
