#include "line.h"

#include "segment.h"

geometry::Line::Line() {
    start_ = Point();
    end_ = Point();
}

int64_t geometry::Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t geometry::Line::GetB() const {
    return start_.GetX() - end_.GetX();
}

int64_t geometry::Line::GetC() const {
    return -GetA() * start_.GetX() - GetB() * start_.GetY();
}

geometry::Line::Line(geometry::Point start, geometry::Point end) {
    start_ = start;
    end_ = end;
}

double geometry::Line::Distance(geometry::Point point) const {
    return std::abs(static_cast<double>(this->GetA() * point.GetX() + this->GetB() * point.GetY() + this->GetC())) /
           std::sqrt(this->GetA() * this->GetA() + this->GetB() * this->GetB());
}

geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
    this->start_.SetX(this->start_.GetX() - vector.GetX());
    this->start_.SetY(this->start_.GetY() - vector.GetY());
    this->end_.SetX(this->end_.GetX() - vector.GetX());
    this->end_.SetY(this->end_.GetY() - vector.GetY());
    return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
    return this->GetA() * point.GetX() + this->GetB() * point.GetY() + this->GetC() == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
    if (this->ContainsPoint(segment.GetStart()) || this->ContainsPoint(segment.GetEnd())) {
        return true;
    }

    if ((this->GetA() * segment.GetStart().GetX() + this->GetB() * segment.GetStart().GetY() + this->GetC() > 0 &&
         this->GetA() * segment.GetEnd().GetX() + this->GetB() * segment.GetEnd().GetY() + this->GetC() < 0) ||
        (this->GetA() * segment.GetStart().GetX() + this->GetB() * segment.GetStart().GetY() + this->GetC() < 0 &&
         this->GetA() * segment.GetEnd().GetX() + this->GetB() * segment.GetEnd().GetY() + this->GetC() > 0)) {
        return true;
    }
    return false;
}

geometry::Line* geometry::Line::Clone() const {
    return new geometry::Line(this->start_, this->end_);
}
