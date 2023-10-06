#pragma once

#include <iostream>
#include <memory>

class Any {
private:
    struct HolderBase {

        virtual ~HolderBase() {
        }

        virtual HolderBase* Clone() const = 0;
    };

    template <class T>
    struct Holder : public HolderBase {

        explicit Holder(const T& val) {
            value_ = val;
        }

        HolderBase* Clone() const override {
            return new Holder<T>(value_);
        }

        T value_;
    };

    HolderBase* ptr_ = nullptr;

public:
    Any();

    template <class T>
    explicit Any(const T& value) {
        ptr_ = new Holder<T>(value);
    }

    template <class T>
    Any& operator=(const T& value) {
        delete ptr_;
        ptr_ = new Holder<T>(value);
        return *this;
    }

    Any(const Any& rhs);
    Any& operator=(Any rhs);
    ~Any();

    bool Empty() const;

    void Clear();
    void Swap(Any& rhs);

    template <class T>
    const T& GetValue() const {
        return dynamic_cast<Holder<T>&>(*ptr_).value_;
    }
};
