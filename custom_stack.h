#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include <iostream>
#include <stdexcept>

template<typename T>
struct ListNode {
    ListNode* next = nullptr;
    T data;

    ListNode(const T& value = T()) : data(value) {};
};

template<typename T>
class custom_stack {
    ListNode<T>* top_;
    std::size_t size_;

    template<typename U>
    friend void print(const custom_stack<U>& stack);

public:
    custom_stack() : size_(0) {};
    custom_stack(const custom_stack& other);
    custom_stack(custom_stack&& other);
    custom_stack& operator=(const custom_stack& other);
    custom_stack& operator=(custom_stack&& other);
    ~custom_stack() {
        clear();
    }

    std::size_t size() {
        return size_;
    }

    bool empty() {
        return size_ == 0;
    }

    void clear() noexcept;
    void push(const T&);
    T pop();
    T& top();
    const T& top() const;
};

template<typename T>
void custom_stack<T>::clear() noexcept {
    while (top_) {
        ListNode<T>* temp = top_;
        top_ = top_->next;
        delete temp;
    }

    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void custom_stack<T>::push(const T& value) {
    ListNode<T>* node = new ListNode<T>(value);
    node->next = top_;
    top_ = node;
    size_++;
}

template<typename T>
T custom_stack<T>::pop() {
    if (!top_) {
        throw std::out_of_range("Stack is empty");
    }

    ListNode<T>* temp = top_;
    T return_value = std::move(top_->data);
    top_ = top_->next;
    delete temp;
    size_--;

    return return_value;
}

template<typename T>
T& custom_stack<T>::top() {
    if (size_ == 0 || !top_ ) {
        throw std::out_of_range("Stack is empty");
    }

    return top_->data;
}

template<typename T>
const T& custom_stack<T>::top() const {
    if (size_ == 0 || !top_ ) {
        throw std::out_of_range("Stack is empty");
    }

    return top_->data;
}

template<typename T>
void print(const custom_stack<T>& stack) {
    std::cout << "Stack (size: " << stack.size_ << "): ";

    ListNode<T>* current = stack.top_;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif  //  CUSTOM_STACK_H