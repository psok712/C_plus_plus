#include "point.h"

#include <cmath>

#include "segment.h"
#include "vector.h"

int64_t geometry::Point::GetX() const {
    return x_coord_;
}

int64_t geometry::Point::GetY() const {
    return y_coord_;
}

void geometry::Point::SetX(int64_t x) {
    x_coord_ = x;
}

void geometry::Point::SetY(int64_t y) {
    y_coord_ = y;
}

geometry::Point &geometry::Point::Move(const geometry::Vector &vector) {
    this->SetX(this->GetX() - vector.GetX());
    this->SetY(this->GetY() - vector.GetY());
    return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point &point) const {
    if (point.GetX() == this->GetX() && point.GetY() == this->GetY()) {
        return true;
    }
    return false;
}

bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
    if ((this->GetX() - segment.GetStart().GetX()) * (segment.GetEnd().GetY() - segment.GetStart().GetY()) -
                (segment.GetEnd().GetX() - segment.GetStart().GetX()) * (this->GetY() - segment.GetStart().GetY()) ==
            0 &&
        (segment.GetStart().GetX() - segment.GetEnd().GetX()) * (segment.GetStart().GetX() - segment.GetEnd().GetX()) >=
            (this->GetX() - segment.GetStart().GetX()) * (segment.GetEnd().GetX() - this->GetX()) &&
        (this->GetX() - segment.GetStart().GetX()) * (segment.GetEnd().GetX() - this->GetX()) >= 0 &&
        (segment.GetStart().GetY() - segment.GetEnd().GetY()) * (segment.GetStart().GetY() - segment.GetEnd().GetY()) >=
            (this->GetY() - segment.GetStart().GetY()) * (segment.GetEnd().GetY() - this->GetY()) &&
        (this->GetY() - segment.GetStart().GetY()) * (segment.GetEnd().GetY() - this->GetY()) >= 0) {
        return true;
    }
    return false;
}

geometry::Point *geometry::Point::Clone() const {
    return new Point(this->GetX(), this->GetY());
}

geometry::Point::Point(int64_t x, int64_t y) {
    this->x_coord_ = x;
    this->y_coord_ = y;
}

geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return geometry::Vector(other.GetX() - this->GetX(), other.GetY() - this->GetY());
}
