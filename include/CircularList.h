#pragma once
#include <iostream>

template <typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size_;

public:
    CircularList() : head(nullptr), tail(nullptr), size_(0) {}

    ~CircularList() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if(!head) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        size_++;
    }

    void print() const {
        if (!head) return;
        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    void clear() {
        if (!head) return;
        Node* current = head;
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);
        head = tail = nullptr;
        size_ = 0;
    }

    size_t size() const { return size_; }

    T& front() { return head->data; }
    const T& front() const { return head->data; }

    T& back() { return tail->data; }
    const T& back() const { return tail->data; }
};
