#ifndef CUSTOM_QUEUE_
#define CUSTOM_QUEUE_

#include <iostream>
#include <stdexcept>

template<typename T>
class custom_queue {
    T* data_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t first_index_;
    std::size_t last_index_;

    void resize() noexcept;

    template<typename U>
    friend void print(const custom_queue<U>& queue);

public:
    custom_queue(std::size_t init_capacity = 10)
        : capacity_(init_capacity),
        size_(0),
        first_index_(0),
        last_index_(0)
    {
        if (init_capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }

        last_index_ = capacity_ - 1;
        data_ = new T[capacity_];
    }

    custom_queue(const custom_queue& other);
    custom_queue(custom_queue&& other) noexcept;
    custom_queue& operator=(const custom_queue& other);
    custom_queue& operator=(custom_queue&& other) noexcept;

    ~custom_queue() {
        delete[] data_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    std::size_t size() const noexcept {
        return size_;
    }

    std::size_t capacity() const noexcept {
        return capacity_;
    }

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push(const T& value);
    T pop();
};

template<typename T>
custom_queue<T>::custom_queue(const custom_queue& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    first_index_ = other.first_index_;
    last_index_ = other.last_index_;

    T* new_data = new T[capacity_];

    for (std::size_t i = 0; i < capacity_; i++) {
        new_data[i] = other.data_[i];
    }

    data_ = new_data;
}

template<typename T>
custom_queue<T>::custom_queue(custom_queue&& other) noexcept {
    capacity_ = other.capacity_;
    size_ = other.size_;
    first_index_ = other.first_index_;
    last_index_ = other.last_index_;
    data_ = other.data_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.first_index_ = 0;
    other.last_index_ = 0;
    other.data_ = nullptr;
}

template<typename T>
custom_queue<T>& custom_queue<T>::operator=(const custom_queue& other) {
    if (this == &other) {
        return *this;
    }

    delete [] data_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    first_index_ = other.first_index_;
    last_index_ = other.last_index_;

    data_ = new T[capacity_];
    for (std::size_t i = 0; i < capacity_; i++) {
        data_[i] = other.data_[i];
    }

    return *this;
}

template<typename T>
custom_queue<T>& custom_queue<T>::operator=(custom_queue&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete [] data_;

    data_ = other.data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    first_index_ = other.first_index_;
    last_index_ = other.last_index_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.first_index_ = 0;
    other.last_index_ = 0;
    other.data_ = nullptr;

    return *this;
}

template<typename T>
void custom_queue<T>::resize() noexcept {
    std::size_t new_capacity = 2 * capacity_;
    T* newData = new(std::nothrow) T[capacity_];

    if (newData == nullptr) { return; }

    for (std::size_t i = 0; i < size_; i++) {
        newData[i] = data_[(first_index_ + i) % capacity_];
    }

    delete [] data_;

    data_ = newData;
    first_index_ = 0;
    last_index_ = size_ - 1;
    capacity_ = new_capacity;
}

template<typename T>
void custom_queue<T>::push(const T& value) {
    if (size_ == capacity_) {
        resize();
    }

    last_index_ = (last_index_ + 1) % capacity_;
    data_[last_index_] = value;
    size_++;
}

template<typename T>
T custom_queue<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }

    T return_value = data_[first_index_];
    first_index_ = (first_index_ + 1) % capacity_;
    size_--;

    return return_value;
}

template<typename T>
T& custom_queue<T>::back() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }

    return data_[last_index_];
}

template<typename T>
const T& custom_queue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }

    return data_[last_index_];
}

template<typename T>
T& custom_queue<T>::front() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data_[first_index_];
}

template<typename T>
const T& custom_queue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data_[first_index_];
}

template<typename T>
void print(const custom_queue<T>& queue) {
    std::cout << "Queue (size: " << queue.size_ << ", capacity: " << queue.capacity_ << "): ";
    for (std::size_t i = 0; i < queue.size_; ++i) {
        std::size_t index = (queue.first_index_ + i) % queue.capacity_;
        std::cout << queue.data_[index] << " ";
    }
    std::cout << std::endl;
}

#endif