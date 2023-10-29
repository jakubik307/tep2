cmake_minimum_required(VERSION 3.23)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab2)

add_executable(lab2
        lab2/main.cpp
        lab2/number.cpp
        lab2/number.h)
