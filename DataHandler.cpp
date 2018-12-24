#include "DataHandler.h"

void DataHandler::SkipCurrentScope() {
    _currentLineIndex = GetEndOfScope(_currentLineIndex);
    if (_currentLineIndex == runUntilLine) {
        StopRun();  //reached last scope end.
    } else {
        _currentLineIndex++;
        HandleStates();
    }
}

bool DataHandler::hasMoreTokens() {
    if (_all_lines.size() <= _currentLineIndex) {
        return false;
    }
    return _all_lines[_currentLineIndex]->size() > _currentTokenIndex;
}

void DataHandler::GoToNextLine() {
    if (_currentLineIndex < _all_lines.size() - 1) {
        _currentLineIndex++;
        _currentTokenIndex = 0;
        HandleStates();
    }
}

void DataHandler::StartRun() {
    _state = RUN;
    runUntilLine = GetEndOfScope(_currentLineIndex);
    _currentLineIndex = GetStartOfScope(runUntilLine);
    _currentTokenIndex = 0;
}

void DataHandler::StopRun() {
    _state = EXECUTE;
    Advance(GetLineSize());
}

void DataHandler::BuildScope() {
    SetState(READ);
    SetTokenIndexToEndOfLine();
}

void DataHandler::Advance(int steps) {
    _currentTokenIndex += steps;
    vector<Token> *currentLine = _all_lines[_currentLineIndex];
    if (_currentTokenIndex >= currentLine->size()) {
        // need to move to next line - if exists!
        GoToNextLine();
    }
}

void DataHandler::SetNewLine(vector<Token> *newLine) {
    this->_skipLine = false;
    this->_all_lines.push_back(newLine);
    this->_currentLineIndex = (int) _all_lines.size() - 1;
    this->_currentTokenIndex = RESET_TOKEN_INDEX;
    HandleStates();
}

int DataHandler::GetEndOfScope(int startLine) {
    int endLine = startLine;
    for (BracketPair *pair : _brackets) {
        if (pair->_openLine == startLine) {
            endLine = pair->_closeLine;
            break;
        }
    }
    return endLine;
}

Token DataHandler::GetTokenInOffSet(int offset) {
    int wanted_index = this->_currentTokenIndex + offset;
    vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
    if (0 <= wanted_index && wanted_index < current_line->size()) {
        return (*current_line)[wanted_index];
    }
    return INDEX_OFFSET_ERR
}

Token DataHandler::GetCurrentToken() {
    vector<Token> *current_line = this->_all_lines[this->_currentLineIndex];
    return (*current_line)[this->_currentTokenIndex];
}

void DataHandler::HandleStates() {
    if (_state == EXECUTE) {
        HandleEXECUTEState();
    } else if (_state == READ) {
        HandleREADState();
    } else if (_state == RUN) {
        HandleRUNState();
    }
}

void DataHandler::HandleRUNState() {
    if (!hasMoreTokens()) {
        GoToNextLine();
    } else if (GetCurrentToken().get_type() == RCB) {
        _currentLineIndex = GetStartOfScope(_currentLineIndex);
    }
}

void DataHandler::HandleREADState() {
    if (hasTokenTypeInCurrentLine(LCB)) {
        AddOpenBracket(_currentLineIndex);
    } else if (hasTokenTypeInCurrentLine(RCB)) {
        if (_openBrackets == START_BRACkETS_NUM) {
            // there are 0 open scopes
            InvalidLineHandle();
        } else if ((_all_lines[_currentLineIndex])->size() > 1) {
            // line has } and more than one token.
            InvalidLineHandle();
        } else {  // there is at least one open scope and valid RCB
            AddCloseBracket(_currentLineIndex);
            if (_openBrackets == START_BRACkETS_NUM) {
                StartRun();
            }
        }
    }
}

void DataHandler::InvalidLineHandle(string extra) {
    cout << INVALID_LINE_ERR << extra << endl;
    _all_lines.erase(_all_lines.end() - 1); // delete last line
    ResetScopeControl();
}

void DataHandler::ResetScopeControl() {
    _state = EXECUTE;
    _openBrackets = START_BRACkETS_NUM;
    _brackets_queue.empty();
}

bool DataHandler::hasTokenTypeInCurrentLine(const TokenType &type) {
    bool result = false;
    for (const Token &token : (*_all_lines[_currentLineIndex])) {
        if (token.get_type() == type) {
            result = true;
            break;
        }
    }
    return result;
}

void DataHandler::HandleEXECUTEState() {
    if (hasTokenTypeInCurrentLine(LCB)) {
        if (!IsBracketPairExists(_currentLineIndex)) {
            // start scope for the first time !
            AddOpenBracket(_currentLineIndex);
        }
    } else if (hasTokenTypeInCurrentLine(RCB)) {
        _currentLineIndex = GetStartOfScope(_currentLineIndex);
    }
}

void DataHandler::AddCloseBracket(int closeLine) {
    BracketPair *pair = _brackets_queue.top();
    _brackets_queue.pop();
    pair->_closeLine = closeLine;
    _openBrackets--;
}

void DataHandler::AddOpenBracket(int startLine) {
    BracketPair *pair = new BracketPair;
    pair->_openLine = startLine;
    pair->_closeLine = startLine;

    _brackets.push_back(pair);
    _brackets_queue.push(pair);
    _openBrackets++;
}

bool DataHandler::IsBracketPairExists(int startLine) {
    bool result = false;
    for (BracketPair *pair : _brackets) {
        if (pair->_openLine == startLine) {
            result = true;
            break;
        }
    }
    return result;
}

int DataHandler::GetStartOfScope(int closeLine) {
    int openLine = closeLine;
    for (BracketPair *pair : _brackets) {
        if (pair->_closeLine == closeLine) {
            openLine = pair->_openLine;
            break;
        }
    }
    return openLine;
}

bool DataHandler::ShouldSkipLine(){
    return _skipLine;
}

void DataHandler::TriggerSkipLine() {
    _skipLine = true;
}