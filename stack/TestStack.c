#include "Stack.h"
#include <stdio.h>
#include <assert.h>


static void test_empty(void) {
    Stack s;
    init(&s);

    assert(isEmpty(&s));

    push(&s, 42);
    assert(!isEmpty(&s));
    pop(&s);
    assert(isEmpty(&s));

    destroy(&s);
    printf("test_empty: OK\n");
}

static void test_lifo(void) {
    Stack s;
    init(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    assert(pop(&s) == 3);
    assert(pop(&s) == 2);
    assert(pop(&s) == 1);
    assert(isEmpty(&s));

    destroy(&s);
    printf("test_lifo: OK\n");
}

static void test_growth(void) {
    Stack s;
    init(&s);

    const int N = 10;
    for (int i = 0; i < N; i++) {
        push(&s, i * 10);
    }

    for (int i = N - 1; i >= 0; i--) {
        assert(pop(&s) == i * 10);
    }
    assert(isEmpty(&s));

    destroy(&s);
    printf("test_growth: OK\n");
}

static void test_stress(void) {
    Stack s;
    init(&s);

    const int N = 1000;
    for (int i = 0; i < N; i++) {
        push(&s, i);
    }
    for (int i = N - 1; i >= 0; i--) {
        assert(pop(&s) == i);
    }
    assert(isEmpty(&s));

    destroy(&s);
    printf("test_stress: OK\n");
}

int main(void) {
    test_empty();
    test_lifo();
    test_growth();
    test_stress();

    printf("\nAll tests completed\n");
    return 0;
}