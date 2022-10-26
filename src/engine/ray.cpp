#include "ray.h"

Ray::Ray(const Point& origin, const Direction& direction) :
    m_origin{origin},
    m_dir{direction}
{}

Point Ray::at(const double t) const {
    return m_origin + (m_dir * t);
}