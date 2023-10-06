#include "cppstring.h"

#include <cstring>

String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

String::String(const String& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (other.data_ == nullptr) {
        data_ = nullptr;
        return;
    }
    data_ = new char[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

String::String(size_t size, char symbol) {
    if (size == 0) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
        return;
    }

    capacity_ = size;
    data_ = new char[size];

    for (size_t i = 0; i < size; ++i) {
        data_[i] = symbol;
    }
    size_ = size;
}

String::String(const char* src) {
    if (src == nullptr) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
        return;
    }
    size_ = std::strlen(src);
    capacity_ = size_;
    data_ = new char[size_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::String(const char* src, size_t size) {
    size_ = size;
    capacity_ = size;
    data_ = new char[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::~String() {
    delete[] data_;
}

String& String::operator=(const String& other) {
    if (&other != this) {
        delete[] data_;
        if (other.data_ == nullptr) {
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            return *this;
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[size_];

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

const char& String::operator[](size_t idx) const {
    return *(data_ + idx);
}

char& String::operator[](size_t idx) {
    return *(data_ + idx);
}

const char& String::At(size_t idx) const {
    if (idx < size_) {
        return *(data_ + idx);
    } else {
        throw StringOutOfRange{};
    }
}

char& String::At(size_t idx) {
    if (idx < size_) {
        return *(data_ + idx);
    } else {
        throw StringOutOfRange{};
    }
}

const char& String::Front() const {
    return data_[0];
}

char& String::Front() {
    return data_[0];
}

const char& String::Back() const {
    return data_[size_ - 1];
}

char& String::Back() {
    return data_[size_ - 1];
}

const char* String::Data() const {
    return data_;
}

char* String::Data() {
    return data_;
}

const char* String::CStr() const {
    return data_;
}

char* String::CStr() {
    return data_;
}

bool String::Empty() const {
    return size_ == 0;
}

size_t String::Size() const {
    return size_;
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    size_ = 0;
}

void String::Swap(String& other) {
    std::swap(other.data_, data_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
}

void String::PopBack() {
    --size_;
}

void String::PushBack(char c) {
    if (size_ >= capacity_) {
        if (capacity_ == 0) {
            Reserve(1);
        } else {
            Reserve(2 * capacity_);
        }
    }
    data_[size_] = c;
    ++size_;
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size > size_) {
        if (new_size > capacity_) {
            Reserve(2 * (new_size + size_));
        }

        for (size_t i = 0; i < new_size; ++i) {
            PushBack(symbol);
        }
    }
    size_ = new_size;
}

void String::Reserve(size_t new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }

    auto str = new char[new_capacity];
    if (data_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
            str[i] = data_[i];
        }
    }
    capacity_ = new_capacity;

    delete[] data_;
    data_ = str;
}

void String::ShrinkToFit() {
    capacity_ = size_;
}

int String::Compare(const String& other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
        if (other.data_[i] < data_[i]) {
            return -1;
        } else if (other.data_[i] > data_[i]) {
            return 1;
        }
    }

    if (other.size_ > size_) {
        return 1;
    } else if (other.size_ < size_) {
        return -1;
    }
    return 0;
}

String& String::operator+=(const String& other) {
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other.data_[i]);
    }
    return *this;
}

String operator+(const String& first, const String& second) {
    auto string = first;
    for (size_t i = 0; i < second.size_; ++i) {
        string.PushBack(second[i]);
    }
    return string;
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}

bool operator==(const String& first, const String& second) {
    if (first.Compare(second) == 0) {
        return true;
    }
    return false;
}

bool operator!=(const String& first, const String& second) {
    if (first.Compare(second) == 0) {
        return false;
    }
    return true;
}

bool operator>(const String& first, const String& second) {
    if (first.Compare(second) == -1) {
        return true;
    }
    return false;
}

bool operator<(const String& first, const String& second) {
    if (first.Compare(second) == 1) {
        return true;
    }
    return false;
}

bool operator>=(const String& first, const String& second) {
    if (first.Compare(second) <= 0) {
        return true;
    }
    return false;
}

bool operator<=(const String& first, const String& second) {
    if (first.Compare(second) >= 0) {
        return true;
    }
    return false;
}

void SafeCpy(char* dest, const char* src, size_t len) {
    const char* temp(src);
    if (temp == NULL) {
        return;
    }
    if (dest == NULL) {
        return;
    }
    while (*temp) {
        if (len > 1) {
            *dest++ = *temp;
            --len;
        }
        ++temp;
    }

    if (len) {
        *dest = '\0';
    }
}
