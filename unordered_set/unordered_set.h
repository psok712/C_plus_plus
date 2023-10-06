#pragma once

#include <functional>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0), data_() {
    }

    explicit UnorderedSet(size_t count) : n_elements_(0), data_() {
        for (size_t i = 0; i < count; ++i) {
            data_.push_back(std::list<KeyT>());
        }
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : n_elements_(0), data_() {
        for (; first != last; ++first) {
            Insert(*first);
        }
    }

    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), data_(other.data_) {
    }

    UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), data_(other.data_) {
        other.Clear();
    }

    ~UnorderedSet() = default;

    UnorderedSet& operator=(const UnorderedSet& other) {
        if (this != &other) {
            n_elements_ = other.n_elements_;
            data_ = other.data_;
        }
        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) {
        if (this != &other) {
            n_elements_ = other.n_elements_;
            data_ = other.data_;
            other.Clear();
        }
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        data_.clear();
        n_elements_ = 0;
    }

    void Insert(const KeyT& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        }

        if (LoadFactor() == 1) {
            Rehash(2 * n_elements_);
        }

        data_[Bucket(key)].push_back(key);
        ++n_elements_;
    }

    void Insert(KeyT&& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        }

        if (LoadFactor() == 1) {
            Rehash(2 * n_elements_);
        }

        data_[Bucket(key)].push_back(std::move(key));
        ++n_elements_;
    }

    void Erase(const KeyT& key) {
        for (auto iterator = data_[Bucket(key)].begin(); iterator != data_[Bucket(key)].end(); ++iterator) {
            if (*iterator == key) {
                data_[Bucket(key)].erase(iterator);
                --n_elements_;
                break;
            }
        }
    }

    bool Find(const KeyT& key) const {
        if (BucketCount() == 0) {
            return false;
        }
        for (auto& elem : data_[Bucket(key)]) {
            if (elem == key) {
                return true;
            }
        }
        return false;
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count < n_elements_) {
            return;
        }

        std::vector<KeyT> vector_elements;

        for (auto& list : data_) {
            for (auto& iterator_list : list) {
                vector_elements.push_back(iterator_list);
            }
        }
        Clear();

        data_ = std::vector<std::list<KeyT>>(new_bucket_count);
        for (auto& elem : vector_elements) {
            data_[Bucket(elem)].push_back(elem);
            ++n_elements_;
        }
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count <= n_elements_) {
            return;
        }

        Rehash(new_bucket_count);
    }

    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        return id >= BucketCount() ? 0 : data_[id].size();
    }

    size_t Bucket(const KeyT& key) const {
        auto id = std::hash<KeyT>{}(key);
        return BucketCount() != 0 ? id % BucketCount() : 0;
    }

    double LoadFactor() const {
        return BucketCount() != 0 ? static_cast<double>(n_elements_) / BucketCount() : 0;
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
