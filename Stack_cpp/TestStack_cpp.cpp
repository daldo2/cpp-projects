#include <cstdio>
#include "Stack_cpp.h"
#include <cassert>

static void test_empty() {
    Stack_cpp s;

    assert(s.is_empty());

    s.push(42);
    assert(!s.is_empty());
    s.pop();
    assert(s.is_empty());

    printf("test_empty: OK\n");
}

static void test_lifo() {
    Stack_cpp s;

    s.push(1);
    s.push(2);
    s.push(3);

    assert(s.pop() == 3);
    assert(s.pop() == 2);
    assert(s.pop() == 1);
    assert(s.is_empty());

    printf("test_lifo: OK\n");
}

static void test_growth() {
    Stack_cpp s;

    const int N = 10;
    for (int i = 0; i < N; i++) {
        s.push(i * 10);
    }

    for (int i = N - 1; i >= 0; i--) {
        assert(s.pop() == i * 10);
    }
    assert(s.is_empty());

    printf("test_growth: OK\n");
}

static void test_stress() {
    Stack_cpp s;

    const int N = 1000;
    for (int i = 0; i < N; i++) {
        s.push(i);
    }
    for (int i = N - 1; i >= 0; i--) {
        assert(s.pop() == i);
    }
    assert(s.is_empty());

    printf("test_stress: OK\n");
}

int main() {
    test_empty();
    test_lifo();
    test_growth();
    test_stress();

    printf("\nAll tests completed\n");
    return 0;
}