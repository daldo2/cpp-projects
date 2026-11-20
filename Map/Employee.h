#pragma once
#include <string>
#include <iostream>

class Employee {
public:
    std::string name;
    std::string position;
    int age;
    Employee(std::string n, std::string p, int a):name(n),position(p),age(a) {}
    friend std::ostream& operator<<(std::ostream& out ,const Employee& e) {
        out << e.name << ", " << e.position<< ", " << e.age;
        return out;
    }
};
