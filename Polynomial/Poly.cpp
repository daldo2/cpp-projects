#include "Poly.h"
#include <cmath>

Poly::Poly() {}
Poly::Poly(double value) {
    if (value != 0 ) {
        dir[0] = value;
    }
}

double &Poly::operator[](int index) {
    return dir[index];
}
double Poly::operator[](int index) const {
    auto it = dir.find(index);
    if (it != dir.end()) {
        return it->second;
    }
    return 0;
}

double Poly::operator()(double x) const {
    double result = 0;
    for (const auto [key,value]: dir) {
        result += std::pow(x, key) *value;
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    bool flag = false;
    for (auto it = poly.dir.rbegin();it != poly.dir.rend(); ++it) {
        int power = it->first;
        double coef = it->second;
        if (coef == 0) {
            continue;
        }

        if (flag == false) {
            if (coef < 0) {
                out << "-";
            }
        }
        else {
            out << (coef < 0 ? " - " : " + ");
        }

        double absCoef = std::abs(coef);
        if (absCoef != 1 || power == 0) {
            out << absCoef;
        }

        if (power == 1) {
            out << "x";
        }
        else if (power > 1) {
            out << "x^" << power;
        }

        flag = true;
    }

    if (flag == false) {
        out << 0;
    }
    return out;
}
Poly operator+(const Poly& left, const Poly& right) {
    Poly result = left;
    for (const auto [key,value]: right.dir) {
        result.dir[key] += value;

        if (result.dir[key] == 0) {
            result.dir.erase(key);
        }
    }
    return result;
}
Poly operator-(const Poly& left, const Poly& right) {
    Poly result = left;
    for (const auto [key,value]: right.dir) {
        result.dir[key] -= value;

        if (result.dir[key] == 0) {
            result.dir.erase(key);
        }
    }
    return result;
}
Poly operator*(const Poly& left, const Poly& right) {
    Poly result;
    for (const auto [key,value]: left.dir) {
        for (const auto[key2,value2]:right.dir) {
            result.dir[key+key2] += value * value2;
            if (result.dir[key+key2] == 0) {
                result.dir.erase(key+key2);
            }
        }
    }
    return result;
}