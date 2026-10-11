#ifndef CPP_PROJECTS_POLY_H
#define CPP_PROJECTS_POLY_H
#include <iostream>
#include <map>

class Poly {
private:
    std::map<int,double> dir;
public:
    Poly();
    Poly(double value);
    double& operator[](int index);
    double operator[](int index) const;

    double operator()(double x) const;
    friend std::ostream &operator<<(std::ostream &out, const Poly &poly);
    friend Poly operator+(const Poly& left,const Poly& right);
    friend Poly operator-(const Poly& left,const Poly& right);
    friend Poly operator*(const Poly& left,const Poly& right);
};

#endif
