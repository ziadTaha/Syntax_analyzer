cmake_minimum_required(VERSION 3.15)
project(CompilerC)

set(CMAKE_CXX_STANDARD 14)

include_directories(Compiler)
include_directories(Compiler/include)

add_executable(CompilerC
        Compiler/include/Controller.h
        Compiler/include/DFA.h
        Compiler/include/DFAState.h
        Compiler/include/NFA.h
        Compiler/include/State.h
        Compiler/include/Token.h
        Compiler/src/Controller.cpp
        Compiler/src/DFA.cpp
        Compiler/src/DFAState.cpp
        Compiler/src/NFA.cpp
        Compiler/src/State.cpp
        Compiler/src/Token.cpp
        Compiler/src/zenyTest.cpp
        Compiler/FirstMaker.cpp
        Compiler/FirstMaker.h
        Compiler/FollowMaker.cpp
        Compiler/FollowMaker.h
        Compiler/main.cpp
        Compiler/Parser.cpp
        Compiler/Parser.h
        Compiler/TableBuilder.cpp
        Compiler/TableBuilder.h)
