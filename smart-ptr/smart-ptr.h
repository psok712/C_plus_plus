#pragma once
#include <cstddef>
#include <string>

template <class T>
class WeakPtr;
struct Counter {
    Counter(std::size_t strong, std::size_t weak) : strong_count(strong), weak_count(weak) {
    }
    Counter(const Counter& other) : strong_count(other.strong_count), weak_count(other.weak_count) {
    }
    std::size_t strong_count;
    std::size_t weak_count;
};
template <class T>
class SharedPtr {
public:
    explicit SharedPtr(const WeakPtr<T>& rhs) : ptr_(rhs.ptr_), counter_(rhs.counter_) {
        if (counter_->strong_count == 0) {
            ptr_ = nullptr;
        }
        ++counter_->strong_count;
    }
    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), counter_(new Counter(1, 0)) {
    }
    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->strong_count;
    }
    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
    }
    ~SharedPtr() {
        Delete();
    }
    auto Reset(T* obj = nullptr) {
        if (obj != ptr_) {
            Delete();
            ptr_ = obj;
            counter_ = new Counter(1, 0);
        }
    }
    auto Swap(T& other) {
        std::swap(*this, other);
    }
    auto Get() {
        return ptr_;
    }
    auto operator*() {
        return *ptr_;
    }
    auto operator->() {
        return ptr_;
    }
    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            Delete();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->strong_count;
        }
        return *this;
    }
    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
        if (this != &other) {
            Delete();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            other.ptr_ = nullptr;
            other.counter_ = nullptr;
        }
        return *this;
    }
    friend class WeakPtr<T>;

private:
    T* ptr_;
    Counter* counter_;
    void Delete() {
        if (counter_) {
            --counter_->strong_count;
            if (counter_->strong_count == 0) {
                delete ptr_;
                if (counter_->weak_count == 0) {
                    delete counter_;
                }
            }
        }
    }
};
template <class T>
class WeakPtr {
public:
    explicit WeakPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->weak_count;
    }
    WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->weak_count;
    }
    WeakPtr(WeakPtr<T>&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
    }
    WeakPtr() : ptr_(nullptr), counter_(new Counter(0, 1)) {
    }
    ~WeakPtr() {
        Delete();
    }
    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        if (this != &other) {
            Delete();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->weak_count;
        }
        return *this;
    }
    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
        if (this != &other) {
            Delete();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            other.ptr_ = nullptr;
            other.counter_ = nullptr;
        }
        return *this;
    }
    bool IsExpired() {
        return counter_->strong_count == 0;
    }
    auto Lock() {
        return IsExpired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }

private:
    T* ptr_;
    Counter* counter_;
    void Delete() {
        if (counter_) {
            --counter_->weak_count;
            if (counter_->strong_count == 0 && counter_->weak_count == 0) {
                delete counter_;
            }
        }
    }
    friend class SharedPtr<T>;
};
