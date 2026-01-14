cmake_minimum_required(VERSION 4.0)
project(L5)

set(CMAKE_CXX_STANDARD 14)

add_executable(L5 main.cpp
        SmartPointer/SmartPointer.tpp
        SmartPointer/SmartPointer.h
        ReferencesCounter/ReferencesCounter.h
        ../L4/Error/Error.cpp
        ../L4/Error/Error.h
        ../L4/Tree/Tree.cpp
        ../L4/Tree/Tree.h
        ../L4/Tree/Node.cpp
        ../L4/Tree/Node.h)
