#include "common/pch.h"

#include "boundingbox.h"

bool BoundingBox::hit(const Ray &ray, double t_min, double t_max) const {
    for (int i = 0; i < 3; i++) {
        const double t0 = fmin(
            (m_minimum[i] - ray.origin()[i]) / ray.direction()[i],
            (m_maximum[i] - ray.origin()[i]) / ray.direction()[i]
        );
        const double t1 = fmax(
            (m_minimum[i] - ray.origin()[i]) / ray.direction()[i],
            (m_maximum[i] - ray.origin()[i]) / ray.direction()[i]
        );
        
        t_min = fmax(t0, t_min);
        t_max = fmin(t1, t_max);
        if (t_min >= t_max) {
            return false;
        }
    }
    return true;
}

Point BoundingBox::min(void) const {
    return m_minimum;
}

Point BoundingBox::max(void) const {
    return m_maximum;
}

BoundingBox BoundingBox::combineBoxes(const BoundingBox &b1, const BoundingBox &b2) {
    Point newMin{
      fmin(b1.min().x(), b2.min().x()),
      fmin(b1.min().y(), b2.min().y()),
      fmin(b1.min().z(), b2.min().z())
    };

    Point newMax{
      fmax(b1.max().x(), b2.max().x()),
      fmax(b1.max().y(), b2.max().y()),
      fmax(b1.max().z(), b2.max().z())
    };

    return BoundingBox{newMin, newMax};
}