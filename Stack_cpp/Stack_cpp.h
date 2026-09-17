#pragma once

class Stack_cpp {
    public:
        int capacity;
        int size;
        int* data;

    Stack_cpp();
    ~Stack_cpp();
    void push(int element);
    int pop();
    bool is_empty();
};