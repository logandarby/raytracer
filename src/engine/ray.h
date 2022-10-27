#ifndef _RAY_H_
#define _RAY_H_

#include "../vec3.h"

class Ray {
public:

    Ray() = default;
    Ray(const Point& origin, const Vec3& direction);

    Point origin() const { return m_origin;  }
    Vec3 direction() const { return m_dir; }

    Point at(const double t) const;

private:
    Point m_origin;
    Vec3 m_dir;
};

#endif