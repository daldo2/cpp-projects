#pragma once
#include <string>
#include <iostream>

enum Status {
    borrowed,
    bookshelf
};

class Book {
public:
    std::string author;
    std::string category;
    int pages;
    Status status;
    Book(std::string a, std::string c,int p,Status s):author(a),category(c),pages(p),status(s){}
    friend std::ostream& operator<<(std::ostream& out ,const Book& book) {
        out << book.author << ", " << book.category<< ", " << book.pages<< ", ";
        if (book.status ==borrowed) {
            out << "borrowed";
        }
        else {
            out << "on the bookshelf";
        }
        return out;
    }
};
