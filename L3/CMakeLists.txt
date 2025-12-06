cmake_minimum_required(VERSION 4.0)
project(L3)

set(CMAKE_CXX_STANDARD 98)

add_executable(L3 main.cpp
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h
        Menu.cpp
        Menu.h)
