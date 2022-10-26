#include "hittableList.h"

bool HittableList::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    bool hitAnything = false;
    double closestSoFar = t_max;
    HitRecord tempRec{};

    for (const auto &object : m_objects) {
        if (object->hit(r, t_min, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}