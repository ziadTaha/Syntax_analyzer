cmake_minimum_required(VERSION 3.15)
project(Syntax_analyzer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Syntax_analyzer
        FirstMaker.cpp
        FirstMaker.h
        FollowMaker.cpp
        FollowMaker.h
        main.cpp
        Parser.cpp
        Parser.h
        TableBuilder.cpp
        TableBuilder.h)
