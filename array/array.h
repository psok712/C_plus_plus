#pragma once

#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array() {
        size_ = 0;
        data_ = nullptr;
    }

    Array(size_t size) {  // NOLINT
        size_ = size;
        data_ = new T[size];
    }

    Array(std::initializer_list<T> list) {
        size_ = list.size();
        data_ = new T[size_];

        for (auto it = list.begin(); it < list.end(); ++it) {
            data_[it - list.begin()] = *it;
        }
    }

    Array(const Array& other) {
        size_ = other.size_;
        data_ = new T[size_];

        for (auto it = other.data_; it < (other.data_ + size_); ++it) {
            data_[it - other.data_] = *it;
        }
    }

    Array& operator=(const Array& other) {
        if (data_ == other.data_) {
            return *this;
        }

        delete[] data_;
        size_ = other.size_;
        data_ = new T[size_];

        for (auto it = other.data_; it < (other.data_ + size_); ++it) {
            data_[it - other.data_] = *it;
        }
        return *this;
    }

    ~Array() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return *(data_ + index);
    }

    const T& operator[](size_t index) const {
        return *(data_ + index);
    }

    size_t size() const {  // NOLINT
        return size_;
    }

    class Iterator {
    public:
        Iterator(T* current) {  // NOLINT
            current_ = current;
        }

        Iterator& operator++() {
            current_ += 1;
            return *this;
        }

        T& operator*() {
            return *current_;
        }

        bool operator!=(const Iterator& other) {
            return current_ != other.current_;
        }

    private:
        T* current_;
    };

    Iterator begin() const {  // NOLINT
        auto it = &data_[0];
        return it;
    }

    Iterator end() const {  // NOLINT
        auto it = &data_[size_];
        return it;
    }
};
