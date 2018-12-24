cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread")

add_executable(ap-firstmilestone main.cpp
        tries.cpp Lexer.h VarManager.h Command.h DataHandler.h
        Expression.h ExpressionManager.h VarCommand.h CommandExpression.h
        EqCommand.h SleepCommand.h PrintCommand.h OpenDataServerCommand.h ConnectCommand.h
        ShuntingYard.h BinaryExpression.h Minus.cpp Minus.h Mult.cpp Mult.h Number.cpp Number.h
        Plus.cpp Plus.h Div.cpp Div.h ConditionalExpression.h SmallEqualConditionalExpression.cpp
        SmallEqualConditionalExpression.h SmallConditionalExpression.cpp SmallConditionalExpression.h
        BigConditionalExpression.cpp BigConditionalExpression.h BigEqualConditionalExpression.cpp
        BigEqualConditionalExpression.h EqualConditionalExpression.cpp EqualConditionalExpression.h
        NotEqualConditionalExpression.cpp
        NotEqualConditionalExpression.h AndConditionalExpression.cpp AndConditionalExpression.h
        OrConditionalExpression.cpp OrConditionalExpression.h WhileCommand.h
        IfCommand.h ScopeCommand.h DataHandler.h DataHandler.cpp
        EqCommand.cpp
        CommandFactory.cpp DataReaderServer.cpp
        CommandFactory.h
        DataReaderServer.h DataReaderClient.cpp DataReaderClient.h ExpressionManager.cpp IfCommand.cpp Lexer.cpp PrintCommand.cpp ScopeCommand.cpp ShuntingYard.cpp SleepCommand.cpp Token.cpp Tokenizer.cpp VarCommand.cpp VarManager.cpp)