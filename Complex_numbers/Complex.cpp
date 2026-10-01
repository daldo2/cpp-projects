#include "Complex.h"
#include <iostream>
#include <stdexcept>

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
    if (other.real * other.real + other.imaginary*other.imaginary == 0) {
        throw std::domain_error("Division by zero");
    }
    double newReal = (real * other.real + imaginary * other.imaginary)/(other.real * other.real + other.imaginary*other.imaginary);
    double newImaginary = (imaginary * other.real - real * other.imaginary)/(other.real * other.real + other.imaginary*other.imaginary);
    real = newReal;
    imaginary = newImaginary;
    return *this;
}
bool Complex::operator==(const Complex& other) const {
    if (imaginary == other.imaginary){
        if (real== other.real) {
            return true;
        }
    }
    return false;
}
bool Complex::operator!=(const Complex& other) const{
    if (imaginary == other.imaginary){
        if (real== other.real) {
            return false;
        }
    }
    return true;
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
std::ostream& operator<<(std::ostream& output, const Complex& value) {
    if (value.imaginary >= 0) {
        return output << value.real << " + " << value.imaginary << "i";
    }
    return output << value.real << " - " << std::abs(value.imaginary) << "i";
}
