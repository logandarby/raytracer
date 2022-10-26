#ifndef _RAY_H_
#define _RAY_H_

#include "../vec3.h"

class Ray {
public:

    Ray() = default;
    Ray(const Point& origin, const Direction& direction);

    Point origin() const { return m_origin;  }
    Direction direction() const { return m_dir; }

    Point at(const double t) const;

private:
    Point m_origin;
    Direction m_dir;
};

#endif