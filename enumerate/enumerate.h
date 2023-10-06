#pragma once

#include <cstring>
#include <functional>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class Iterator>
class EnumerateIterator {
public:
    explicit EnumerateIterator(Iterator ptr) : iterator_(ptr), index_(0) {
    }

    bool operator!=(EnumerateIterator other) {
        return iterator_ != other.iterator_;
    }

    auto operator++() {
        ++iterator_;
        ++index_;
        return *this;
    }

    auto operator*() {
        return std::make_pair(index_, std::ref(*iterator_));
    }

private:
    Iterator iterator_;
    size_t index_;
};

template <typename Container>
auto Enumerate(Container &container) {
    return IteratorRange(EnumerateIterator(container.begin()), EnumerateIterator(container.end()));
}
