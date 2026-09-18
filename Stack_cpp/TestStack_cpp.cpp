#include <cstdio>
#include "Stack_cpp.h"
#include <cassert>

#include "../stack/Stack.h"

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

static void test_assign_copy() {
    Stack_cpp s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack_cpp s2(s1);
    assert(s2.size == 3);
    assert(s2.capacity == 3);
    assert(s2.data != s1.data);

    assert(s2.pop() == 3);
    assert(s2.pop() == 2);
    assert(s2.pop() == 1);
    assert(s2.is_empty());

    assert(s1.size == 3);
    assert(!s1.is_empty());

    Stack_cpp s3 = s1;
    assert(s3.size == 3);
    assert(s3.capacity == 3);
    assert(s3.data != s1.data);

    assert(s3.pop() == 3);
    assert(s3.pop() == 2);
    assert(s3.pop() == 1);
    assert(s3.is_empty());

    assert(s1.size == 3);
    assert(!s1.is_empty());

    Stack_cpp s4;

    s4.push(10);
    int* previous_data = s4.data;
    s4 = s1;
    assert(s4.data == previous_data);
    assert(s4.size == 3);
    assert(s4.pop() == 3);
    assert(s4.pop() == 2);
    assert(s4.pop() == 1);
    assert(s1.size == 3);

    printf("test_assign_copy: OK\n");
}
//testy przy braniu stosu do funkcji po adresie i po wskazniku

int main() {
    test_empty();
    test_lifo();
    test_growth();
    test_stress();
    test_assign_copy();

    printf("\nAll tests completed\n");
    return 0;
}