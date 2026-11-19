#include <iostream>
#include <fstream>
#include <cassert>
#include "Matrix.h"

void read_test() {
    Matrix first(10,10) ;
    bool catched = false;
    try {
        first(6,0);
    } catch (const IndexOutOfRange&) {
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
    } catch (IndexOutOfRange&) {
        catched = true;
    }
    assert(catched);
    std::cout << "read_out_of_range_test: passed\n";
}

void negative_index_test() {
    Matrix m(3,3);
    bool catched = false;
    try {
        m(-1,0);
    } catch (IndexOutOfRange&) {
        catched = true;
    }
    assert(catched);
    std::cout << "negative_index_test: passed\n";
}

void write_out_of_range_test() {
    Matrix m(3,3);
    bool catched = false;
    try {
        m(5,0) = 3;
    } catch (IndexOutOfRange&) {
        catched = true;
    }
    assert(catched);
    std::cout << "write_out_of_range_test: passed\n";
}

void three_references_test() {
    Matrix a(2,2);
    Matrix b = a;
    Matrix c(3,3);
    c = a;
    assert(a.getReferences() == 3);
    assert(b.getReferences() == 3);
    assert(c.getReferences() == 3);

    a = a;
    assert(a.getReferences() == 3);
    std::cout << "three_references_test: passed\n";
}

void detach_test() {
    Matrix a(2,2);
    a(0,0) = 1;
    Matrix b = a;
    Matrix c = a;
    assert(a.getReferences() == 3);

    b(0,0) = 5;
    assert(b.getReferences() == 1);
    assert(a.getReferences() == 2);
    assert(b(0,0) == 5);
    assert(a(0,0) == 1);
    assert(c(0,0) == 1);
    std::cout << "detach_test: passed\n";
}

void references_to_zero_test() {
    Matrix* a = new Matrix(2,2);
    Matrix* b = new Matrix(*a);
    Matrix* c = new Matrix(*a);
    assert(a->getReferences() == 3);

    delete b;
    delete c;
    assert(a->getReferences() == 1);
    delete a;
    std::cout << "references_to_zero_test: passed\n";
}

void cell_read_write_test() {
    Matrix a(2,2);
    a(1,1) = 7;
    Matrix b = a;

    double x = b(1,1);
    assert(x == 7);
    assert(a.getReferences() == 2);

    b(0,1) = 4;
    assert(b.getReferences() == 1);

    a(0,0) = b(0,1);
    assert(a(0,0) == 4);
    std::cout << "cell_read_write_test: passed\n";
}

Matrix make2x2(double p, double q, double r, double s) {
    Matrix m(2,2);
    m(0,0) = p; m(0,1) = q;
    m(1,0) = r; m(1,1) = s;
    return m;
}

void arithmetic_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = make2x2(5, 6, 7, 8);

    assert((a + b) == make2x2(6, 8, 10, 12));
    assert((b - a) == make2x2(4, 4, 4, 4));
    assert((a * b) == make2x2(19, 22, 43, 50));

    Matrix rect(2,3);
    bool catched = false;
    try {
        a + rect;
    } catch (IncorrectDimensions&) {
        catched = true;
    }
    assert(catched);
    std::cout << "arithmetic_test: passed\n";
}

void arithmetic_assign_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = make2x2(5, 6, 7, 8);

    a += b;
    assert(a == make2x2(6, 8, 10, 12));

    a -= b;
    assert(a == make2x2(1, 2, 3, 4));

    a *= b;
    assert(a == make2x2(19, 22, 43, 50));
    std::cout << "arithmetic_assign_test: passed\n";
}

void arithmetic_assign_shared_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = a;
    Matrix x = make2x2(1, 1, 1, 1);
    assert(a.getReferences() == 2);

    a += x;
    assert(a == make2x2(2, 3, 4, 5));
    assert(b == make2x2(1, 2, 3, 4));
    assert(a.getReferences() == 1);
    assert(b.getReferences() == 1);
    std::cout << "arithmetic_assign_shared_test: passed\n";
}

void comparison_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = make2x2(1, 2, 3, 4);
    Matrix c = make2x2(1, 2, 3, 9);

    assert(a == b);
    assert(a != c);
    std::cout << "comparison_test: passed\n";
}

void output_operator_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    std::ofstream out("output.txt");
    out << a;
    out.close();

    std::ifstream in("output.txt");
    double x, y, z, w;
    in >> x >> y >> z >> w;
    assert(x == 1 && y == 2 && z == 3 && w == 4);
    std::cout << "output_operator_test: passed\n";
}

void read_from_file_test() {
    std::ifstream file("read.csv");
    Matrix m(1,1);
    m.readFromFile(file);
    assert(m.getRows() == 4);
    assert(m.getCols() == 5);
    assert(m(1,2) == 60.2);

    std::ifstream missing("no_such_file.csv");
    bool catched = false;
    try {
        m.readFromFile(missing);
    } catch (FileError&) {
        catched = true;
    }
    assert(catched);
    std::cout << "read_from_file_test: passed\n";
}

void read_bad_data_test() {
    std::ofstream out("bad.txt");
    out << "2 2\n1 2 abc";
    out.close();

    std::ifstream in("bad.txt");
    Matrix m(1,1);
    bool catched = false;
    try {
        m.readFromFile(in);
    } catch (FileError&) {
        catched = true;
    }
    assert(catched);
    std::cout << "read_bad_data_test: passed\n";
}

void constructor_dimensions_test() {
    bool catched = false;
    try {
        Matrix m(0,3);
    } catch (IncorrectDimensions&) {
        catched = true;
    }
    assert(catched);
    std::cout << "constructor_dimensions_test: passed\n";
}

int main() {
    read_test();
    read_out_of_range_test();
    negative_index_test();
    write_out_of_range_test();
    three_references_test();
    detach_test();
    references_to_zero_test();
    cell_read_write_test();
    arithmetic_test();
    arithmetic_assign_test();
    arithmetic_assign_shared_test();
    comparison_test();
    output_operator_test();
    read_from_file_test();
    read_bad_data_test();
    constructor_dimensions_test();
    std::cout << "ALL TESTS PASSED\n";
}
