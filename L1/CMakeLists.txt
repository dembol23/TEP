cmake_minimum_required(VERSION 4.0)
project(L1)

set(CMAKE_CXX_STANDARD 98)

add_executable(L1 tableAllocation.cpp
        main.cpp
        tableAllocation.h
        TwoDTable.cpp
        TwoDTable.h
        CTable.cpp
        CTable.h
)

