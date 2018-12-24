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
#define INVALID_LINE_ERR "syntax error occurs in line: " << _currentLineIndex
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
    bool _skipLine;

    recv_state _state;

    int runUntilLine;   // main scope last line - '}'
    int _openBrackets;  // number of currently unclosed brackets - in READ state
    vector<BracketPair *> _brackets;  // all brackets pairs - keep track
    stack<BracketPair *> _brackets_queue; // for building main scopes.

    int GetStartOfScope(int closeLine);

    bool IsBracketPairExists(int startLine);

    void AddOpenBracket(int startLine);

    void AddCloseBracket(int closeLine);

    void HandleEXECUTEState();

    bool hasTokenTypeInCurrentLine(const TokenType &type);

    void ResetScopeControl();

    // upon invalid line - resets scope control and continue with EXECUTE mode.

    void HandleREADState();

    void HandleRUNState();

    void HandleStates();

public:

    DataHandler() {
        this->_currentLineIndex = RESET_LINE_INDEX;
        this->_state = EXECUTE;
        this->_openBrackets = 0;
        this->_skipLine = false;
    }

    // Getters
    Token GetCurrentToken();

    Token GetTokenInOffSet(int offset);

    recv_state GetState() {
        return this->_state;
    }

    int GetCurrentLineIndex() {
        return this->_currentLineIndex;
    }

    int GetLineSize() {
        return (int) _all_lines[_currentLineIndex]->size();
    }

    int GetEndOfScope(int startLine);

    // functionality for data control
    void SetNewLine(vector<Token> *newLine);

    void Advance(int steps);

    void SetState(recv_state _state) {
        this->_state = _state;
    }

    void SetTokenIndexToEndOfLine() {
        _currentTokenIndex = (int) _all_lines[_currentLineIndex]->size();
    }

    void TriggerSkipLine();

    void BuildScope();

    void StartRun();

    void StopRun();

    void GoToNextLine();

    void InvalidLineHandle(string extra);

    /**
     * is called on the first line of the scope.
     */
    void SkipCurrentScope();

    // Information functions
    bool hasMoreTokens();

    bool ShouldSkipLine();

    bool IsScopeReady(int scopeLine) { return _openBrackets == 0; }
};

#endif
