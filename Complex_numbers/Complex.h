#ifndef STACK_CPP_COMPLEX_H
#define STACK_CPP_COMPLEX_H
#include <iosfwd>


class Complex {
    public:
        double real;
        double imaginary;

        Complex(double r, double i = 0);
        Complex& operator+=(const Complex& other);
        Complex& operator-=(const Complex& other);
        Complex& operator*=(const Complex& other);
        Complex& operator/=(const Complex& other);
        double phase() const;
        double amplitude() const;
};
Complex operator+(Complex left, const Complex& right);
Complex operator-(Complex left, const Complex& right);
Complex operator*(Complex left, const Complex& right);
Complex operator/(Complex left, const Complex& right);
bool operator==(Complex left, const Complex& right) ;
bool operator!=(Complex left, const Complex& right) ;
std::ostream& operator<<(std::ostream& output, const Complex& value);


#endif
