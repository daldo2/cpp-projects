#include "Complex.h"
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

static void test_addition() {
    Complex a(1,2);
    Complex b(1,5);
    Complex c(0,0);
    Complex d(3.5,-0.5);

    Complex sum1 = a + b;
    assert(sum1 == Complex(2,7));
    Complex sum2 = a + c;
    assert(sum2 == Complex(1,2) );
    Complex sum3 = sum1 + sum2;
    assert(sum3 == Complex(3,9) );
    Complex sum4 = sum3 + c;
    assert(sum4 == sum3);
    Complex sum5 = b + d;
    assert(sum5 == Complex(4.5,4.5));

    cout << "test_addition: OK\n";
}
static void test_substraction() {
    const Complex a(1,2);
    const Complex b(1,5);
    const Complex c(0,0);
    const Complex d(3.5,-0.5);

    Complex sum1 = a - b;
    assert(sum1 == Complex(0,-3));
    Complex sum2 = a - c;
    assert(sum2 == Complex(1,2) );
    Complex sum3 = sum1 - sum2;
    assert(sum3 == Complex(-1,-5) );
    Complex sum4 = sum3 + c;
    assert(sum4 == sum3);
    Complex sum5 = b - d;
    assert(sum5 == Complex(-2.5,5.5));

    cout << "test_substraction: OK\n";
}
static void test_multiplication() {
    Complex a(1,2);
    Complex b(3,4);
    Complex c(2,1);
    Complex d(2,-1);
    Complex e(0,1);

    Complex sum1 = a * b;
    assert(sum1 == Complex(-5,10));
    Complex sum2 = c * d;
    assert(sum2 == Complex(5,0));\
    Complex sum3 = e * e;
    assert(sum3 == Complex(-1,0));

    cout << "test_multiplication: OK\n";
}
static void test_division() {
    Complex a(4,2);
    Complex b(1,1);
    Complex c(5,5);
    Complex d(1,1);

    Complex sum1 = a / b;
    assert(sum1 == Complex(3,-1));
    Complex sum2 = c / d;
    assert(sum2 == Complex(5,0));

    cout << "test_division: OK\n";
}
static void test_division_by_zero() {
    Complex number(4, 2);
    Complex zero(0, 0);

    bool exception_caught = false;
    try {
        number = number / zero;
    }
    catch (std::domain_error&) {
        exception_caught = true;
    }
    assert(exception_caught);
    assert(number.real == 4);
    assert(number.imaginary == 2);

    cout << "test_division_by_zero: OK\n";
}

static void test_output() {
    ostringstream positive;
    positive << Complex(5, 8);
    assert(positive.str() == "5 + 8i");

    ostringstream negative;
    negative << Complex(5, -8);
    assert(negative.str() == "5 - 8i");

    ostringstream zero;
    zero << Complex(5, 0);
    assert(zero.str() == "5 + 0i");

    ostringstream chained;
    chained << Complex(1, 2) << " | " << Complex(3, -4);
    assert(chained.str() == "1 + 2i | 3 - 4i");

    cout << "test_output: OK\n";
    //I used ai here to test it right
}
int main() {
    test_addition();
    test_substraction();
    test_multiplication();
    test_division();
    test_division_by_zero();
    test_output();
}
//Almost equal might be necessary, professor need to be asked
//Tests for == and != needed