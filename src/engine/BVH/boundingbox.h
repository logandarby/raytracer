#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "common/vec3.h"
#include "../ray.h"

class BoundingBox {
public:
    BoundingBox(const Point min = V_ORIGIN, const Point max = V_UNIT) :
        m_minimum{min},
        m_maximum{max} 
    {}

    bool hit(const Ray &ray, double t_min, double t_max) const;

    Point min() const;
    Point max() const;

    static BoundingBox combineBoxes(const BoundingBox &b1, const BoundingBox &b2);

private:
    Point m_minimum;
    Point m_maximum;
};

#endif