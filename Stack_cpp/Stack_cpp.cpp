#include "Stack_cpp.h"
#include <cstdlib>
#include <iostream>

class Stack_cpp {
    public:
        int capacity;
        int size;
        int* data;

        Stack_cpp() {
            capacity = 4;
            size = 0;
            data = (int*)malloc(sizeof(int)* capacity);
        }

        ~Stack_cpp() {
                free(data);
        }

        void push(int element) {
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

        int pop() {
            if (is_empty()) {
                std::cout << "No items in Stack";
                exit(EXIT_FAILURE);
            }
            int element = data[size-1];
            size --;
            return element;
        }

        bool is_empty() {
            return size == 0;
        }
};
// if (s->size == s->capacity) {
//     size_t new_capacity = s-> capacity * 2;
//     int* new_data = realloc(s->data,sizeof(int) * new_capacity);
//     if (new_data == NULL) {
//         destroy(s);
//         fprintf(stderr, "push: No memory\n");
//         exit(EXIT_FAILURE);
//     }
// int pop(Stack* s) {
//     if (isEmpty(s)) {
//         destroy(s);
//         fprintf(stderr, "pop: No items in stack\n");
//         exit(EXIT_FAILURE);
//     }
//     int value = s->data[s->size-1];
//     s->size --;
//     return value;
//
// }