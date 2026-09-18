#pragma once

class Stack_cpp {
public:
    int capacity;
    int size;
    int* data;

    Stack_cpp();
    ~Stack_cpp();
    Stack_cpp& operator=(const Stack_cpp& other);
    Stack_cpp(const Stack_cpp &other);

    void push(int element);
    int pop();
    bool is_empty();
};