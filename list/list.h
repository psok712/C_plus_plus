#pragma once

#include <algorithm>
#include <cstddef>

template <typename T>
class List {
private:
    struct ListNode {
        ListNode() : next(nullptr), prev(nullptr) {
        }

        ListNode(ListNode* next, ListNode* prev) : next(next), prev(prev) {
        }

        virtual ~ListNode() {
        }

        ListNode* next;
        ListNode* prev;
    };

    struct ListNodeWithValue : public ListNode {
        explicit ListNodeWithValue(const T& value) : ListNode(), value(value) {
        }

        ListNodeWithValue(const T& value, ListNode* next, ListNode* prev) : ListNode(next, prev), value(value) {
        }

        explicit ListNodeWithValue(T&& value) : ListNode(), value(std::move(value)) {
        }

        ListNodeWithValue(T&& value, ListNode* next, ListNode* prev) : ListNode(next, prev), value(std::move(value)) {
        }

        T value;
    };

    ListNode* fictive_element_;
    size_t size_;

    void LinkAfter(ListNode* new_element, ListNode* target) {
        new_element->prev = target;
        new_element->next = target->next;
        new_element->next->prev = new_element;
        target->next = new_element;
        ++size_;
    }

    void UnLink(ListNode* to_delete) {
        auto prev = to_delete->prev;
        auto next = to_delete->next;
        delete to_delete;
        prev->next = next;
        next->prev = prev;
        --size_;
    }

public:
    class Iterator {
    public:
        Iterator() = default;

        explicit Iterator(ListNode* other) : current_(other) {
        }

        Iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        Iterator operator++(int) {
            auto old_current = *this;
            current_ = current_->next;
            return old_current;
        }

        Iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }

        Iterator operator--(int) {
            auto old_current = *this;
            current_ = current_->prev;
            return old_current;
        }

        T& operator*() const {
            return static_cast<ListNodeWithValue*>(current_)->value;
        }

        T* operator->() const {
            return static_cast<ListNodeWithValue*>(current_)->value;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

    private:
        ListNode* current_;
    };

    List() : fictive_element_(new ListNode()), size_(0) {
        fictive_element_->next = fictive_element_;
        fictive_element_->prev = fictive_element_;
    }

    List(const List& other) : List() {
        for (auto elem : other) {
            PushBack(elem);
        }
    }

    List(List&& other) : fictive_element_(other.fictive_element_), size_(other.size_) {
        other.fictive_element_ = nullptr;
        other.size_ = 0;
    }

    ~List() {
        while (size_) {
            PopBack();
        }
        delete fictive_element_;
    }

    List& operator=(const List& list) {
        if (this != &list) {
            while (size_) {
                PopBack();
            }

            for (auto it : list) {
                PushBack(it);
            }
        }
        return *this;
    }

    List& operator=(List&& list) noexcept {
        if (this != &list) {
            while (size_) {
                PopBack();
            }
            delete fictive_element_;

            fictive_element_ = list.fictive_element_;
            size_ = list.size_;

            list.fictive_element_ = nullptr;
            list.size_ = 0;
        }
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        ListNode* new_elem = new ListNodeWithValue(elem, nullptr, nullptr);
        LinkAfter(new_elem, fictive_element_->prev);
    }

    void PushBack(T&& elem) {
        ListNode* new_elem = new ListNodeWithValue(std::move(elem), nullptr, nullptr);
        LinkAfter(new_elem, fictive_element_->prev);
    }

    void PushFront(const T& elem) {
        ListNode* new_elem = new ListNodeWithValue(elem, nullptr, nullptr);
        LinkAfter(new_elem, fictive_element_);
    }

    void PushFront(T&& elem) {
        ListNode* new_elem = new ListNodeWithValue(std::move(elem), nullptr, nullptr);
        LinkAfter(new_elem, fictive_element_);
    }

    T& Front() {
        return static_cast<ListNodeWithValue*>(fictive_element_->next)->value;
    }

    const T& Front() const {
        return static_cast<ListNodeWithValue*>(fictive_element_->next)->value;
    }

    T& Back() {
        return static_cast<ListNodeWithValue*>(fictive_element_->prev)->value;
    }

    const T& Back() const {
        return static_cast<ListNodeWithValue*>(fictive_element_->prev)->value;
    }

    void PopBack() {
        UnLink(fictive_element_->prev);
    }

    void PopFront() {
        UnLink(fictive_element_->next);
    }

    Iterator Begin() {
        return Iterator(fictive_element_->next);
    }

    Iterator End() {
        return Iterator(fictive_element_);
    }

    Iterator begin() const {  // NOLINT
        return Iterator(fictive_element_->next);
    }

    Iterator end() const {  // NOLINT
        return Iterator(fictive_element_);
    }
};
