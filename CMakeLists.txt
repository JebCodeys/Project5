cmake_minimum_required(VERSION 3.15)
project(Project5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hashing main.cpp
        OpenAddressing.h
        SeparateChaining.h)
