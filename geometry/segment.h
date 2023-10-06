#include <vector>

#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    Segment();

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    double Distance(Point) const;

    bool Degenerate() const;

    Segment& Move(const Vector& vector) override {
        this->start_.SetX(this->GetStart().GetX() - vector.GetX());
        this->start_.SetY(this->GetStart().GetY() - vector.GetY());
        this->end_.SetX(this->GetEnd().GetX() - vector.GetX());
        this->end_.SetY(this->GetEnd().GetY() - vector.GetY());
        return *this;
    }

    bool ContainsPoint(const Point& point) const override {
        if ((point.GetX() - this->GetStart().GetX()) * (this->GetEnd().GetY() - this->GetStart().GetY()) -
                    (this->GetEnd().GetX() - this->GetStart().GetX()) * (point.GetY() - this->GetStart().GetY()) ==
                0 &&
            (this->GetStart().GetX() - this->GetEnd().GetX()) * (this->GetStart().GetX() - this->GetEnd().GetX()) >=
                (point.GetX() - this->GetStart().GetX()) * (this->GetEnd().GetX() - point.GetX()) &&
            (point.GetX() - this->GetStart().GetX()) * (this->GetEnd().GetX() - point.GetX()) >= 0 &&
            (this->GetStart().GetY() - this->GetEnd().GetY()) * (this->GetStart().GetY() - this->GetEnd().GetY()) >=
                (point.GetY() - this->GetStart().GetY()) * (this->GetEnd().GetY() - point.GetY()) &&
            (point.GetY() - this->GetStart().GetY()) * (this->GetEnd().GetY() - point.GetY()) >= 0) {
            return true;
        }
        return false;
    }

    bool CrossesSegment(const Segment& segment) const override {
        geometry::Point a = this->GetStart();
        geometry::Point b = this->GetEnd();
        geometry::Point c = segment.GetStart();
        geometry::Point d = segment.GetEnd();
        auto ab = a - b;
        auto cd = c - d;

        if (this->ContainsPoint(segment.GetStart()) || this->ContainsPoint(segment.GetEnd()) ||
            segment.ContainsPoint(this->GetEnd()) || segment.ContainsPoint(this->GetStart())) {
            return true;
        }

        if (VectorMult(ab, a - c) * VectorMult(ab, a - d) >= 0) {
            return false;
        }

        if (VectorMult(cd, c - a) * VectorMult(cd, c - b) >= 0) {
            return false;
        }

        return true;
    };

    Segment* Clone() const override {
        geometry::Segment* new_segment = new geometry::Segment(this->start_, this->end_);
        return new_segment;
    };
};
}  // namespace geometry
