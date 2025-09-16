#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <initializer_list>
#include <iostream>

template<typename T>
struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    T value;

    Node(const T& data = T()) : value(data) {}
};

template<typename T>
class List {
    Node<T>* head;
    Node<T>* tail;
    std::size_t sz;

    template <typename U>
    friend void print(const List<U>& list);

public:
    List() : head(nullptr), tail(nullptr) {}

    List(std::initializer_list<T> init_list) : head(nullptr), tail(nullptr) {
        for (const auto& data : init_list) {
            push_back(data);
        }
    }

    List(const List& other) {
        // Тут прроверку на самого себя
        head = nullptr;
        tail = nullptr;

        for (Node<T>* cur = other.head; cur != nullptr; cur = cur->next) {
            continue;
        }
    }

    List(const List&& other) {
        if (this == &other) {
            return;
        }

        head(other.head);
        tail(other.tail);

        other.head = nullptr;
        other.tail = nullptr;
    }

    List<T>& operator=(const List<T>& other) {
        return other;
    }

    List<T>& operator=(List<T>&& other) noexcept {
        if (this == &other) {
            return other;
        }

        clear();
        head = other.head;
        tail = other.tail;

        sz = other.sz;

        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }

    ~List() {
        clear();
    }

    bool empty() const noexcept {
        return head == nullptr;
    }

    std::size_t size() const noexcept {
        return sz;
    }

    void clear() noexcept;
    void push_back(const T& data);
    void pop_back();
    void push_front(const T& data);
    void pop_front();;
    void insert();
};

template<typename T>
void List<T>::clear() noexcept {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    sz = 0;
}

template<typename T>
void List<T>::push_back(const T& data) {
    Node<T>* node = new Node(data);
    if (!tail) {
        tail = head = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    sz++;
}

template<typename T>
void List<T>::push_front(const T& data) {
    Node<T>* node = new Node(data);
    if (!tail) {
        tail = head = node;
    }
    else {
        head->prev = node;
        node->next = head;
        head = node;
    }
    sz++;
}

template<typename T>
void List<T>::pop_back() {
    if (!tail) {
        return;
    }

    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }

    delete temp;
    sz--;
}

template<typename T>
void List<T>::pop_front() {
    if (!head) {
        return;
    }

    Node<T>* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }

    delete temp;
    sz--;
}

template<typename T>
void print(const List<T>& list) {
    for (Node<T>* node = list.head; node; ) {
        std::cout << node->value;
        if (node->next) {
            std::cout << ", ";
        }
        node = node->next;
    }
    std::cout << std::endl;
}

#endif // CUSTOM_LIST_H
