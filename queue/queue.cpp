#include "queue.h"

Node::Node(int32_t value, Node* next) {
    this->value = value;
    this->next = next;
}

Queue::Queue() {
    front_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    Node* tmp = new Node(value, nullptr);
    if (Empty()) {
        front_ = tmp;
        tail_ = tmp;
    } else {
        tail_->next = tmp;
        tail_ = tail_->next;
    }
    ++size_;
}

void Queue::Pop() {
    auto tmp = front_;
    front_ = front_->next;
    delete tmp;
    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (!Empty()) {
        Pop();
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}
