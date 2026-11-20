#pragma once
#include <iostream>

class DuplicateKey {};

template <class K,class V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node *next;
        Node(const K& k, const V& v, Node* n): key(k), value(v), next(n) {}
    };
    Node *head;
    void clear() {
        Node* tail = head;
        while (tail != nullptr) {
            tail = tail->next;
            delete head;
            head = tail;
        }
    }
    void copyFrom(const Map& other) {
        Node* tail = nullptr;
        head = nullptr;
        for (auto it = other.head; it!= nullptr; it = it->next) {
            Node* current = new Node(it->key,it->value,nullptr);
            if (head == nullptr) {
                head = current;
            }
            else {
                tail->next = current;
            }
            tail = current;
        }
    }
    bool keyAlreadyExists(const K& k) {
        if (head == nullptr) {
            return false;
        }
        Node* tail = head;
        while (tail != nullptr) {
            if (tail->key == k) {
                return true;
            }
            tail = tail->next;
        }
        return false;
    }
public:
    Map() {
        head = nullptr;
    }
    Map(const Map& other) {
        copyFrom(other);
    }
    ~Map() {
        clear();
    }
    Map& operator=(const Map& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        copyFrom(other);
        return *this;
    }
    void add(const K& k, const V& v) {
        if (keyAlreadyExists(k)) {
            throw DuplicateKey();
        }
        if (head != nullptr) {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new Node(k,v,nullptr);
        }
        else {
            head = new Node(k,v,nullptr);
        }
    }
    V* find(const K& k) {
        Node* tail = head;
        while (tail != nullptr) {
            if (tail->key == k) {
                return &tail->value;
            }
            tail = tail->next;
        }
        return nullptr;
    }
    friend std::ostream& operator<<(std::ostream& out, const Map& m) {
        Node* tail = m.head;
        while (tail != nullptr) {
            out << tail->key <<" || "<< tail->value << "\n";
            tail = tail->next;
        }
        return out;
    }
};
