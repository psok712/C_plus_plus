#include "segment.h"

#include "line.h"

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}

geometry::Segment::Segment(geometry::Point start, geometry::Point end) {
    this->start_ = start;
    this->end_ = end;
}

geometry::Segment::Segment() {
    this->start_ = geometry::Point();
    this->end_ = geometry::Point();
}

double geometry::Segment::Distance(geometry::Point point) const {
    geometry::Line line(this->GetStart(), this->GetEnd());
    return line.Distance(point);
}
