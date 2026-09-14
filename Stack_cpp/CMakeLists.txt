cmake_minimum_required(VERSION 3.20)

project(Stack_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Stack_cpp
        Stack_cpp.cpp
        Stack_cpp.h
        TestStack_cpp.cpp
        TestStack_cpp.h
)
