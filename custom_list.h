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
    std::size_t size_;

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
        head = nullptr;
        tail = nullptr;

        for (Node<T>* cur = other.head; cur != nullptr; cur = cur->next) {
            continue;
        }
    }

    List(List&& other) noexcept {
        head(other.head);
        tail(other.tail);

        other.head = nullptr;
        other.tail = nullptr;
    }

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;
    T& operator[](const std::size_t& index);
    const T& operator[](const std::size_t& index) const;

    ~List() {
        clear();
    }

    bool empty() const noexcept {
        return head == nullptr;
    }

    std::size_t size() const noexcept {
        return size_;
    }

    void clear() noexcept;
    void push_back(const T& data);
    void pop_back();
    void push_front(const T& data);
    void pop_front();
    void insert(std::size_t index, const T& value);
    void erase(std::size_t index);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
};

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) {
        return *this;
    }

    clear();

    Node<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }

    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    head = other.head;
    tail = other.tail;

    size_ = other.size_;

    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;

    return *this;
}

template<typename T>
void List<T>::clear() noexcept {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    size_ = 0;
}

template<typename T>
void List<T>::push_back(const T& data) {
    Node<T>* node = new Node<T>(data);
    if (!tail) {
        tail = head = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size_++;
}

template<typename T>
void List<T>::push_front(const T& data) {
    Node<T>* node = new Node<T>(data);
    if (!tail) {
        tail = head = node;
    }
    else {
        head->prev = node;
        node->next = head;
        head = node;
    }
    size_++;
}

template<typename T>
void List<T>::insert(std::size_t index, const T& value) {
    if (index >= size_) {
        return;
    }

    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == size) {
        push_back(value);
        return;
    }

    Node<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    Node<T>* new_node = new Node<T>(value);
    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
    size_++;
}

template<typename T>
void List<T>::erase(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("List index out of range");
    }

    if (index == 0) {
        pop_front();
    }
    if (index == size - 1) {
        pop_back();
    }

    Node<T>* current = head;
    for (std::size_t i = 0; i < index; i++) {
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;
    size_--;

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
    size_--;
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
    size_--;
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

template<typename T>
T& List<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    Node<T>* current = nullptr;
    if (index > size_ / 2) {
        current = tail;
        for (std::size_t i = size_ - 1; i > index; i--) {
            current = current->prev;
        }
    }
    else {
        current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next;
        }
    }

    return current->data;
}

template<typename T>
const T& List<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    Node<T>* current = nullptr;
    if (index > size_ / 2) {
        current = tail;
        for (std::size_t i = size_ - 1; i > index; i--) {
            current = current->prev;
        }
    }
    else {
        current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next;
        }
    }

    return current->data;
}

#endif // CUSTOM_LIST_H
