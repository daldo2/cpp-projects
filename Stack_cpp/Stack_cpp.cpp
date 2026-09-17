#include "Stack_cpp.h"
#include <cstdlib>
#include <iostream>

Stack_cpp::Stack_cpp() {
    capacity = 4;
    size = 0;
    data = (int*)malloc(sizeof(int)* capacity);
}
Stack_cpp::Stack_cpp(const Stack_cpp& other) {
    capacity = other.capacity;
    size = other.size;
    data = (int*)malloc(sizeof(int)* capacity); //Check how it should be coppied exacly
}

Stack_cpp::~Stack_cpp() {
        free(data);
}

void Stack_cpp::push(int element) {
    if (size == capacity) {
        size_t new_capacity = capacity * 2;
        int* new_data = (int*)realloc(data,sizeof(int) * new_capacity);
        if (new_data == nullptr) {
            std::cout << "Ups";
            exit(EXIT_FAILURE);
        }
        capacity = new_capacity;
        data = new_data;
    }
    data[size] = element;
    size ++;
}

int Stack_cpp::pop() {
    if (is_empty()) {
        std::cout << "No items in Stack";
        exit(EXIT_FAILURE);
    }
    int element = data[size-1];
    size --;
    return element;
}

bool Stack_cpp::is_empty() {
    return size == 0;
}
/* copy constructor
 * assigment constructor
*/