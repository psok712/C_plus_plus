#include "ray.h"

#include "line.h"
#include "segment.h"
namespace geometry {
Ray::Ray() {
    start_ = Point();
    end_ = Point();
}
Ray::Ray(Point first, Point second) {
    start_ = first;
    end_ = second;
}
Ray& Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool Ray::ContainsPoint(const Point& point) const {
    Line line(start_, end_);
    return line.ContainsPoint(point) &&
           (Segment(start_, end_).ContainsPoint(point) || Segment(start_, point).ContainsPoint(end_));
}
bool Ray::CrossesSegment(const Segment& segment) const {
    Line line(start_, end_);
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd()) || segment.ContainsPoint(start_)) {
        return true;
    }
    if (!line.CrossesSegment(segment)) {
        return false;
    }
    const int64_t expansion_coef = 10000;
    Point new_end = Point(end_.GetX() * expansion_coef, end_.GetY() * expansion_coef);
    return Segment(start_, new_end).CrossesSegment(segment);
}
Ray* Ray::Clone() const {
    Ray* ray = new Ray(start_, end_);
    return ray;
}
Point Ray::GetStart() const {
    return start_;
}
Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry
