#include "vector.h"

geometry::Vector::Vector() {
    x_coord_ = 0;
    y_coord_ = 0;
}

geometry::Vector::Vector(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

int64_t geometry::Vector::GetX() const {
    return x_coord_;
}

int64_t geometry::Vector::GetY() const {
    return y_coord_;
}

geometry::Vector geometry::Vector::operator+(const geometry::Vector &other) const {
    return geometry::Vector(this->x_coord_ + other.x_coord_, this->y_coord_ + other.y_coord_);
}

geometry::Vector geometry::Vector::operator-(const geometry::Vector &other) const {
    return geometry::Vector(this->x_coord_ - other.x_coord_, this->y_coord_ - other.y_coord_);
}

geometry::Vector geometry::Vector::operator+() const {
    return geometry::Vector(+this->x_coord_, +this->y_coord_);
}

geometry::Vector geometry::Vector::operator-() const {
    return geometry::Vector(+this->x_coord_, +this->y_coord_);
}

geometry::Vector geometry::Vector::operator*(int64_t number) const {
    return geometry::Vector(this->x_coord_ * number, this->y_coord_ * number);
}

geometry::Vector geometry::Vector::operator/(int64_t number) const {
    return geometry::Vector(this->x_coord_ / number, this->y_coord_ / number);
}

geometry::Vector &geometry::Vector::operator+=(const geometry::Vector &other) {
    this->x_coord_ = this->x_coord_ + other.x_coord_;
    this->y_coord_ = this->y_coord_ + other.y_coord_;
    return *this;
}

geometry::Vector &geometry::Vector::operator-=(const geometry::Vector &other) {
    this->x_coord_ = this->x_coord_ - other.x_coord_;
    this->y_coord_ = this->y_coord_ - other.y_coord_;
    return *this;
}

geometry::Vector &geometry::Vector::operator*=(int64_t number) {
    this->x_coord_ = this->x_coord_ * number;
    this->y_coord_ = this->y_coord_ * number;
    return *this;
}

geometry::Vector &geometry::Vector::operator/=(int64_t number) {
    this->x_coord_ = this->x_coord_ / number;
    this->y_coord_ = this->y_coord_ / number;
    return *this;
}

bool geometry::Vector::operator==(const geometry::Vector &other) const {
    return (this->x_coord_ == other.x_coord_) && (this->y_coord_ == other.y_coord_);
}
