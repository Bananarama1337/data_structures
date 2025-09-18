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

    void deep_copy(const custom_stack& other);

public:
    custom_stack() : size_(0) {};
    custom_stack(const custom_stack& other);
    custom_stack(custom_stack&& other) noexcept;
    custom_stack& operator=(const custom_stack& other);
    custom_stack& operator=(custom_stack&& other) noexcept;
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
void custom_stack<T>::deep_copy(const custom_stack& other) {
    top_ = new ListNode<T>(other.top_->data);
    ListNode<T>* thisCurrent = top_;
    ListNode<T>* otherCurrent = other.top_->next;

    while (otherCurrent) {
        thisCurrent->next = new ListNode<T>(otherCurrent->data);
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    }
}

template<typename T>
custom_stack<T>::custom_stack(const custom_stack& other) {
    size_ = other.size_;
    top_ = nullptr;

    if (!other.top_) return; 

    deep_copy(other);
}

template<typename T>
custom_stack<T>::custom_stack(custom_stack&& other) noexcept {
    size_ = other.size_;
    top_ = other.top_;

    other.size_ = 0;
    other.top_ = nullptr;
}

template<typename T>
custom_stack<T>& custom_stack<T>::operator=(const custom_stack& other) {
    if (this == &other) {
        return *this;
    }

    clear();

    size_ = other.size_;
    top_ = nullptr;

    if (!other.top_) return *this;

    deep_copy(other);

    return *this;
}

template<typename T>
custom_stack<T>& custom_stack<T>::operator=(custom_stack&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    size_ = other.size_;
    top_ = other.top_;

    other.size_ = 0;
    other.top_ = nullptr;

    return *this;
}

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
    std::cout << "Stack (size: " << stack.size_ << "): top -> ";

    ListNode<T>* current = stack.top_;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif  //  CUSTOM_STACK_H