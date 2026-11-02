#include <iostream>
#include <cassert>
#include "Matrix.h"

void read_test() {
    Matrix first(10,10) ;
    bool catched = false;
    try {
        first(6,0);
    }catch(const IndexOutOfRange&) {
        catched = true;
    }
    assert(!catched);
    std::cout << "read_test: passed\n";
}
void read_out_of_range_test() {
    Matrix first(10,10) ;
    bool catched = false;
    try {
        first(10,0);
    }catch(IndexOutOfRange&) {
        catched = true;
    }
    assert(catched);
    std::cout << "read_out_of_range_test: passed\n";
}
int main() {
    read_test();
    read_out_of_range_test();
}
