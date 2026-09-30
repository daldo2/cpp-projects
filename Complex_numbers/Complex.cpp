#include "Complex.h"

Complex::Complex(double r, double i) {
    imaginary = i;
    real = r;
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}
Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}
Complex& Complex::operator*=(const Complex& other) {
    double newReal = (real * other.real - imaginary * other.imaginary);
    double newImaginary = (real * other.imaginary + imaginary * other.real);
    real = newReal;
    imaginary = newImaginary;
    return *this;
}
Complex& Complex::operator/=(const Complex& other) {
    double newReal = (real * other.real + imaginary * other.imaginary)/(other.real * other.real + other.imaginary*other.imaginary);
    double newImaginary = (imaginary * other.real - real * other.imaginary)/(other.real * other.real + other.imaginary*other.imaginary);
    real = newReal;
    imaginary = newImaginary;
    return *this;
}



Complex operator+(Complex left, const Complex& right) {
    left += right;
    return left;
}
Complex operator-(Complex left, const Complex& right) {
    left -= right;
    return left;
}
Complex operator*(Complex left, const Complex& right) {
    left *= right;
    return left;
}
Complex operator/(Complex left, const Complex& right) {
    left /= right;
    return left;
}
