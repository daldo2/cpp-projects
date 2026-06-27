#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void init(Stack* s) {
    s->capacity = 4;
    s->size = 0;
    s->data = malloc(sizeof(int) * s->capacity);
    if (s->data == NULL) {
        fprintf(stderr, "init: No memory\n");
        exit(EXIT_FAILURE);
    }
}

void destroy(Stack* s) {
    free(s->data);
    s->data = NULL;
    s->capacity = 0;
    s->size = 0;
}

void push(Stack* s, int element) {

    if (s->size == s->capacity) {
        size_t new_capacity = s-> capacity * 2;
        int* new_data = realloc(s->data,sizeof(int) * new_capacity);
        if (new_data == NULL) {
            destroy(s);
            fprintf(stderr, "push: No memory\n");
            exit(EXIT_FAILURE);
        }

        s->capacity = new_capacity;
        s->data = new_data;
    }
    s->data[s->size] = element;
    s->size ++;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        destroy(s);
        fprintf(stderr, "pop: No items in stack\n");
        exit(EXIT_FAILURE);
    }
    int value = s->data[s->size-1];
    s->size --;
    return value;

}

bool isEmpty(const Stack* s) {
    return s->size == 0;
}

