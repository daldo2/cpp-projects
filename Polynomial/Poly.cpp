#include "Poly.h"
#include <cmath>

Poly::Poly(double value) {
    if (value != 0 ) {
        coeffs[0] = value;
    }
}

double &Poly::operator[](int index) {
    if (index < 0) {
        throw std::out_of_range("Negative index value");
    }
    return coeffs[index];
}
double Poly::operator[](int index) const {
    if (index < 0) {
        throw std::out_of_range("Negative index value");
    }
    auto it = coeffs.find(index);
    if (it != coeffs.end()) {
        return it->second;
    }
    return 0;
}

double Poly::operator()(double x) const {
    double result = 0;
    for (const auto [key,value]: coeffs) {
        result += std::pow(x, key) *value;
    }
    return result;
}

void outputTerm(double absCoef,int power,std::ostream& out) {
    if (absCoef != 1 || power == 0) {
        out << absCoef;
    }

    if (power == 1) {
        out << "x";
    }
    else if (power > 1) {
        out << "x^" << power;
    }
}

void outputSign(double coef,bool isFirstTerm, std::ostream& out){
    if (isFirstTerm) {
        if (coef < 0) {
            out << "-";
        }
    }
    else {
        if (coef < 0) {
            out << " - ";
        }
        else {
            out <<" + ";
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    bool isFirstTerm = true;
    for (auto it = poly.coeffs.rbegin();it != poly.coeffs.rend(); ++it) {
        int power = it->first;
        double coef = it->second;
        if (coef == 0) {
            continue;
        }
        outputSign(coef,isFirstTerm,out);
        double absCoef = std::abs(coef);
        outputTerm(absCoef,power,out);
        isFirstTerm = false;
    }

    if (isFirstTerm) {
        out << 0;
    }
    return out;
}

Poly operator+(const Poly& left, const Poly& right) {
    Poly result = left;
    for (const auto [key,value]: right.coeffs) {
        result.coeffs[key] += value;

        if (result.coeffs[key] == 0) {
            result.coeffs.erase(key);
        }
    }
    return result;
}
Poly operator-(const Poly& left, const Poly& right) {
    Poly result = left;
    for (const auto [key,value]: right.coeffs) {
        result.coeffs[key] -= value;

        if (result.coeffs[key] == 0) {
            result.coeffs.erase(key);
        }
    }
    return result;
}
Poly operator*(const Poly& left, const Poly& right) {
    Poly result;
    for (const auto [key,value]: left.coeffs) {
        for (const auto[key2,value2]:right.coeffs) {
            result.coeffs[key+key2] += value * value2;
            if (result.coeffs[key+key2] == 0) {
                result.coeffs.erase(key+key2);
            }
        }
    }
    return result;
}