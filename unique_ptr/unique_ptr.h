#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() {
        ptr_ = nullptr;
    }

    explicit UniquePtr(T *ptr) {
        ptr_ = ptr;
    }

    UniquePtr(UniquePtr &&other) : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr<T> &operator=(UniquePtr<T> &&ptr) noexcept {
        if (this != &ptr) {
            delete ptr_;
            ptr_ = ptr.ptr_;
            ptr.ptr_ = nullptr;
        }
        return *this;
    }

    void Reset(T *ptr) {
        delete ptr_;
        ptr_ = ptr;
    }

    void Reset() {
        if (ptr_) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }

    T *operator->() const {
        return ptr_;
    }

private:
    T *ptr_;
};
