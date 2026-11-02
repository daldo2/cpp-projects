#include "Matrix.h"
#include <fstream>

CommonMatrix::CommonMatrix(int a, int b) {
    rows = a;
    cols = b;
    data = new double*[a];
    for (int i = 0; i < a; i++) {
        data[i] = new double[b]();
    }
    references = 1;
}
CommonMatrix::CommonMatrix(const CommonMatrix &other) {
    rows = other.rows;
    cols = other.cols;
    data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            data[i][j]  = other.data[i][j];
        }
    }
    references =  1;

}
CommonMatrix::~CommonMatrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}
bool CommonMatrix::rowExists(int a, int b)const{
    if (a < 0 || a >= rows) {
        return false;
    }
    if (b < 0 || b >= cols) {
        return false;
    }
    return true;
}

Matrix::Matrix(int a, int b) {
    block = new CommonMatrix(a,b);
}
Matrix::Matrix(const Matrix& other) {
    block = other.block;
    block->references += 1;
}
Matrix::~Matrix() {
    release();
}

double Matrix::read(int a, int b) const {
    return block->data[a][b];
}
void Matrix::write(int a, int b, double v) {
    detach();
    block->data[a][b] = v;
}
void Matrix::release(){
    block->references -= 1;
    if (block->references == 0) {
        delete block;
    }
}

Matrix& Matrix::detach() {
    if (getReferences() == 1) {
        return *this;
    }
    CommonMatrix *newblock = new CommonMatrix(*block);
    block->references -= 1;
    block = newblock;
    return *this;
}

int Matrix::getRows() const {
    return block->rows;
}
int Matrix::getCols() const {
    return block->cols;
}
int Matrix::getReferences() const {
    return block->references;
}

Matrix Matrix::operator+(const Matrix& other)const {
    int rows = getRows();
    int cols = getCols();
    if (other.getCols() != cols || other.getRows() != rows) {
        throw IncorrectDimensions();
    }
    Matrix result(rows,cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j<cols; j++) {
            double addition = read(i,j) + other.read(i,j);
            result.block->data[i][j]= addition;
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& other)const{
    int rows = getRows();
    int cols = getCols();
    if (other.getCols() != cols || other.getRows() != rows) {
        throw IncorrectDimensions();
    }
    Matrix result(rows,cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j<cols; j++) {
            double difference = read(i,j) - other.read(i,j);
            result.block->data[i][j]= difference;
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& other)const{
    int rowsA = getRows();
    int colsA = getCols();
    int rowsB = other.getRows();
    int colsB = other.getCols();
    if (colsA!= rowsB ) {
        throw IncorrectDimensions();
    }
    Matrix result(rowsA,colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j<colsB; j++) {
            double sum = 0;
            for (int k = 0; k < colsA; k++) {
                sum += read(i,k) * other.read(k,j);
            }
            result(i,j) = sum;
        }
    }
    return result;
}
Matrix& Matrix::operator+=(const Matrix& other){
    Matrix result = *this + other;
    *this = result;
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other){
    Matrix result = *this - other;
    *this = result;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other){
    Matrix result = *this * other;
    *this = result;
    return *this;
}
bool Matrix::operator==(const Matrix& other) const{
    int rows = getRows();
    int cols = getCols();
    if (other.getCols() != cols || other.getRows() != rows) {
        return false;
    }
    if (this == &other) {
        return true;
    }
    if (block != other.block) {
        return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix& other) const{
    return !(*this == other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    this->release();
    block = other.block;
    block->references += 1;
    return *this;
}
double Matrix::operator()(int a, int b)const{
    if (!block->rowExists(a,b)) {
        throw IndexOutOfRange();
    }
    return block->data[a][b];
}
Matrix& Matrix::readFromFile() {
    int rows = 4;
    int cols = 5;
    std::string myText;

    // Read from the text file
    std::ifstream MyReadFile("read.csv");
    
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        cout << myText;
    }

    // Close the file
    MyReadFile.close();
}
Matrix::Cell Matrix::operator()(int a, int b) {
    if (!block->rowExists(a, b)) {
        throw IndexOutOfRange();
    }
    return Cell(*this, a, b);
}
Matrix::Cell& Matrix::Cell::operator=(double v) {
    matrix.write(row, col, v);
    return *this;
}
Matrix::Cell& Matrix::Cell::operator=(const Cell& other) {
    return *this = double(other);
}

Matrix::Cell::Cell(Matrix& matrix, int row, int col)
    : matrix(matrix), row(row), col(col)
{}
Matrix::Cell::operator double() const {
    return matrix.read(row, col);
}

std::ostream& operator<<(std::ostream& out,const Matrix& matrix) {
    for (int i = 0; i < matrix.getRows(); i++) {
        for (int j = 0; j < matrix.getCols(); j++) {
            out << matrix(i,j) << " ";
        }
        out << "\n";
    }
    return out;
}