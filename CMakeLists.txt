cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread")

add_executable(ap-firstmilestone main.cpp tries.cpp Lexer.h VarManager.h
        Command.h CommandFactory.h DataHandler.h Expression.h
        ExpressionManager.h Utils.h VarCommand.h CommandExpression.h
        EqCommand.h SleepCommand.h PrintCommand.h OpenDataServerCommand.h
        ConnectCommand.h Token.h Tokenizer.h)