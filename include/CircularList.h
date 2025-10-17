#pragma once
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <iostream>

template <typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size_;

public:
    CircularList() noexcept : head(nullptr), tail(nullptr), size_(0) {}
    CircularList(const CircularList& other) : CircularList() {
        for (const auto& v : other) push_back(v);
    }
    CircularList(CircularList&& other) noexcept : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }
    CircularList& operator=(CircularList other) noexcept {
        swap(other);
        return *this;
    }
    ~CircularList() { clear(); }

    // basic ops
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        push_node_back(newNode);
    }
    void push_back(T&& value) {
        Node* newNode = new Node(std::move(value));
        push_node_back(newNode);
    }

    void pop_front() {
        if (!head) throw std::out_of_range("pop_front on empty list");
        if (size_ == 1) {
            delete head;
            head = tail = nullptr;
            size_ = 0;
            return;
        }
        Node* old = head;
        head = head->next;
        tail->next = head;
        delete old;
        --size_;
    }

    void pop_back() {
        if (!head) throw std::out_of_range("pop_back on empty list");
        if (size_ == 1) {
            delete tail;
            head = tail = nullptr;
            size_ = 0;
            return;
        }
        // find prev of tail (we have single link, so walk)
        Node* cur = head;
        while (cur->next != tail) cur = cur->next;
        delete tail;
        tail = cur;
        tail->next = head;
        --size_;
    }

    T& front() {
        if (!head) throw std::out_of_range("front on empty list");
        return head->data;
    }
    const T& front() const {
        if (!head) throw std::out_of_range("front on empty list");
        return head->data;
    }

    T& back() {
        if (!tail) throw std::out_of_range("back on empty list");
        return tail->data;
    }
    const T& back() const {
        if (!tail) throw std::out_of_range("back on empty list");
        return tail->data;
    }

    void clear() noexcept {
        if (!head) return;
        Node* cur = head->next;
        while (cur != head) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        delete head;
        head = tail = nullptr;
        size_ = 0;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    void swap(CircularList& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
    }

    // iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : node_(nullptr), root_(nullptr), at_end_(true) {}
        reference operator*() const { return node_->data; }
        pointer operator->() const { return &node_->data; }

        iterator& operator++() {
            if (!node_) return *this;
            node_ = node_->next;
            if (node_ == root_) { node_ = nullptr; at_end_ = true; }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& o) const { return node_ == o.node_; }
        bool operator!=(const iterator& o) const { return !(*this == o); }

    private:
        Node* node_;
        Node* root_;
        bool at_end_;
        friend class CircularList;
        iterator(Node* n, Node* root) : node_(n), root_(root), at_end_(n==nullptr) {}
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : node_(nullptr), root_(nullptr), at_end_(true) {}
        const_iterator(const iterator& it) : node_(it.node_), root_(it.root_), at_end_(it.at_end_) {}
        reference operator*() const { return node_->data; }
        pointer operator->() const { return &node_->data; }

        const_iterator& operator++() {
            if (!node_) return *this;
            node_ = node_->next;
            if (node_ == root_) { node_ = nullptr; at_end_ = true; }
            return *this;
        }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const const_iterator& o) const { return node_ == o.node_; }
        bool operator!=(const const_iterator& o) const { return !(*this == o); }

    private:
        Node* node_;
        Node* root_;
        bool at_end_;
        friend class CircularList;
        const_iterator(Node* n, Node* root) : node_(n), root_(root), at_end_(n==nullptr) {}
    };

    iterator begin() noexcept { return iterator(head, head); }
    iterator end() noexcept { return iterator(nullptr, head); }
    const_iterator begin() const noexcept { return const_iterator(head, head); }
    const_iterator end() const noexcept { return const_iterator(nullptr, head); }
    const_iterator cbegin() const noexcept { return const_iterator(head, head); }
    const_iterator cend() const noexcept { return const_iterator(nullptr, head); }

private:
    void push_node_back(Node* newNode) {
        if (!head) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        ++size_;
    }
};
