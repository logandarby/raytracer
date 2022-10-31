#include "hittableList.h"
#include "BVH/boundingbox.h"

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

bool HittableList::boundingBox(BoundingBox &outputBox) const {
    if (m_objects.empty()) {
        return false;
    }

    BoundingBox temp{V_ORIGIN, V_UNIT};
    bool firstBox = true;
    for (auto &object : m_objects) {
        if (!object->boundingBox(temp)) {
           return false;
        }
        if (firstBox) {
            outputBox = temp;
            firstBox = false;
        } else {
            outputBox = BoundingBox::combineBoxes(temp, outputBox);
        }
    }

    return true;
}