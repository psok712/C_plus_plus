#include "stack.h"

Node::Node(int32_t value, Node *previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    head_ = nullptr;
    size_ = 0;
}

Stack::~Stack() {
    while (size_ > 1) {
        auto new_head = head_->previous;
        delete head_;
        head_ = new_head;
        --size_;
    }
    size_ = 0;
    delete head_;
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    size_++;
}

void Stack::Pop() {
    auto previous_head = head_->previous;
    delete head_;
    head_ = previous_head;
    size_--;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (size_ > 1) {
        auto new_head = head_->previous;
        delete head_;
        head_ = new_head;
        --size_;
    }
    size_ = 0;
    head_ = nullptr;
}

bool Stack::Empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}
