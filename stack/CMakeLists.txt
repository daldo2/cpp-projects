cmake_minimum_required(VERSION 4.2)
project(stack C)

set(CMAKE_C_STANDARD 11)

add_executable(stack main.c
        TestStack.c
        Stack.h
        Stack.c)
