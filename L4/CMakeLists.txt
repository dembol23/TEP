cmake_minimum_required(VERSION 4.0)
project(L4)

set(CMAKE_CXX_STANDARD 11)

add_executable(L4 main.cpp
        Error/Error.cpp
        Error/Error.h
        Result/Result.hpp
        Tree/Node.cpp
        Tree/Node.h
        Tree/Tree.cpp
        Tree/Tree.h
        Tree/Menu.cpp
        Tree/Menu.h
        FileSaver/FileSaver.h
        Result/Result.tpp)
