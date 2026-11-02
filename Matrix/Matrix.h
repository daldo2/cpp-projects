#ifndef CPP_PROJECTS_MATRIX_H
#define CPP_PROJECTS_MATRIX_H
#include <iostream>

class IndexOutOfRange {};
class IncorrectDimensions{};

class CommonMatrix {
private:
    int rows,cols;
    double **data;
    int references;
    CommonMatrix(int a, int b);
    CommonMatrix(const CommonMatrix& other);
    ~CommonMatrix();
    bool rowExists(int a, int b)const;
    friend class Matrix;
};

class Matrix {
private:
    CommonMatrix* block;
    void release();
    double read(int a, int b) const;
    void write(int a, int b, double v);
    Matrix& detach();
public:
    class Cell {
    private:
        Matrix& matrix;
        int row, col;
    public:
        Cell(Matrix& matrix, int row, int col);
        operator double() const;
        Cell& operator=(double v);
        Cell& operator=(const Cell& other);
    };
    Matrix(int a, int b);
    ~Matrix() ;
    Matrix(const Matrix& other);
    int getRows() const;
    int getCols() const;
    int getReferences() const;
    Matrix& operator=(const Matrix& other);
    double operator()(int a, int b) const;
    Cell operator()(int a, int b);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix& readFromFile();
};

std::ostream& operator<<(std::ostream& out,const Matrix& matrix);

#endif //CPP_PROJECTS_MATRIX_H
