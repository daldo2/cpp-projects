#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    assert(c.getReferences() == 2);
    assert(b(0,0) == 5);
    assert(a(0,0) == 1);
    assert(c(0,0) == 1);
    std::cout << "detach_test: passed\n";
}

void references_to_zero_test() {
    Matrix* a = new Matrix(2,2);
    {
        Matrix b = *a;
        Matrix c = *a;
        assert(a->getReferences() == 3);
    }
    assert(a->getReferences() == 1);
    delete a;
    std::cout << "references_to_zero_test: passed\n";
}

void cell_read_write_test() {
    Matrix a(2,2);
    a(1,1) = 7;
    Matrix b = a;
    Matrix c = a;

    double x = b(1,1);
    assert(x == 7);
    assert(a.getReferences() == 3);

    const Matrix& cref = c;
    assert(cref(1,1) == 7);
    assert(a.getReferences() == 3);

    b(0,1) = 4;
    assert(b.getReferences() == 1);
    assert(a.getReferences() == 2);

    a(0,0) = b(0,1);
    assert(a(0,0) == 4);
    assert(a.getReferences() == 1);
    assert(c(0,0) == 0);
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
    assert(a == make2x2(1, 2, 3, 4));

    Matrix rect(2,3);
    bool catched = false;
    try { a + rect; } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    catched = false;
    try { a - rect; } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    catched = false;
    try { rect * a; } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    std::cout << "arithmetic_test: passed\n";
}

void compound_assignment_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = make2x2(5, 6, 7, 8);
    Matrix copy = a;

    a += b;
    assert(a == make2x2(6, 8, 10, 12));
    assert(copy == make2x2(1, 2, 3, 4));

    a -= b;
    assert(a == make2x2(1, 2, 3, 4));

    a *= b;
    assert(a == make2x2(19, 22, 43, 50));

    Matrix rect(2,3);
    bool catched = false;
    try { a += rect; } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    assert(a == make2x2(19, 22, 43, 50));
    std::cout << "compound_assignment_test: passed\n";
}

void comparison_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = make2x2(1, 2, 3, 4);
    Matrix c = make2x2(1, 2, 3, 9);
    Matrix d(2,3);

    assert(a == b);
    assert(!(a != b));
    assert(a != c);
    assert(a != d);
    std::cout << "comparison_test: passed\n";
}

void output_operator_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    std::ostringstream out;
    out << a;
    assert(out.str() == "1 2 \n3 4 \n");
    std::cout << "output_operator_test: passed\n";
}

void read_from_file_test() {
    std::ifstream file("read.csv");
    Matrix m(1,1);
    m.readFromFile(file);
    assert(m.getRows() == 4);
    assert(m.getCols() == 5);
    assert(m(0,4) == 2.5);
    assert(m(1,2) == 60.2);
    assert(m(3,0) == 4.7);

    std::ifstream missing("no_such_file.csv");
    bool catched = false;
    try { m.readFromFile(missing); } catch (FileError&) { catched = true; }
    assert(catched);
    assert(m.getRows() == 4);

    std::istringstream bad("2 2\n1 2 abc");
    catched = false;
    try { m.readFromFile(bad); } catch (FileError&) { catched = true; }
    assert(catched);

    std::istringstream zero("0 3");
    catched = false;
    try { m.readFromFile(zero); } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    std::cout << "read_from_file_test: passed\n";
}

void constructor_dimensions_test() {
    bool catched = false;
    try { Matrix m(0,3); } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    catched = false;
    try { Matrix m(2,-1); } catch (IncorrectDimensions&) { catched = true; }
    assert(catched);
    std::cout << "constructor_dimensions_test: passed\n";
}

void non_square_multiplication_test() {
    Matrix a(2,3);
    a(0,0) = 1; a(0,1) = 2; a(0,2) = 3;
    a(1,0) = 4; a(1,1) = 5; a(1,2) = 6;
    Matrix b(3,2);
    b(0,0) = 7;  b(0,1) = 8;
    b(1,0) = 9;  b(1,1) = 10;
    b(2,0) = 11; b(2,1) = 12;

    Matrix c = a * b;
    assert(c.getRows() == 2);
    assert(c.getCols() == 2);
    assert(c == make2x2(58, 64, 139, 154));

    Matrix d = b * a;
    assert(d.getRows() == 3);
    assert(d.getCols() == 3);
    assert(d(0,0) == 39);
    assert(d(2,2) == 105);
    std::cout << "non_square_multiplication_test: passed\n";
}

void compound_assignment_shared_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = a;
    Matrix x = make2x2(1, 1, 1, 1);
    assert(a.getReferences() == 2);

    a += x;
    assert(a == make2x2(2, 3, 4, 5));
    assert(b == make2x2(1, 2, 3, 4));
    assert(a.getReferences() == 1);
    assert(b.getReferences() == 1);

    Matrix c = b;
    c *= x;
    assert(c == make2x2(3, 3, 7, 7));
    assert(b == make2x2(1, 2, 3, 4));
    std::cout << "compound_assignment_shared_test: passed\n";
}

void read_from_file_shared_test() {
    Matrix a = make2x2(1, 2, 3, 4);
    Matrix b = a;
    assert(a.getReferences() == 2);

    std::istringstream in("1 3\n7 8 9");
    a.readFromFile(in);
    assert(a.getRows() == 1);
    assert(a.getCols() == 3);
    assert(a(0,2) == 9);
    assert(b == make2x2(1, 2, 3, 4));
    assert(a.getReferences() == 1);
    assert(b.getReferences() == 1);
    std::cout << "read_from_file_shared_test: passed\n";
}

void index_out_of_range_test() {
    Matrix m(3,3);
    const Matrix& cm = m;

    bool catched = false;
    try { m(-1,0); } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);

    catched = false;
    try { m(0,-1); } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);

    catched = false;
    try { m(0,3); } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);

    catched = false;
    try { m(5,0) = 3; } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);

    catched = false;
    try { cm(3,0); } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);

    catched = false;
    try { cm(-1,-1); } catch (IndexOutOfRange&) { catched = true; }
    assert(catched);
    std::cout << "index_out_of_range_test: passed\n";
}

int main() {
    read_test();
    read_out_of_range_test();
    three_references_test();
    detach_test();
    references_to_zero_test();
    cell_read_write_test();
    arithmetic_test();
    compound_assignment_test();
    comparison_test();
    output_operator_test();
    read_from_file_test();
    constructor_dimensions_test();
    non_square_multiplication_test();
    compound_assignment_shared_test();
    read_from_file_shared_test();
    index_out_of_range_test();
    std::cout << "ALL TESTS PASSED\n";
}
