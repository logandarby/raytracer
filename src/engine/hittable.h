#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "ray.h"

#include <memory>

class Material;

struct HitRecord {
    Point p;
    Vec3 normal;
    double t;
    std::shared_ptr<Material> materialPtr;
    bool frontFace;

    // Sets the normal to face against the incident ray
    void setFaceNormal(const Ray &r, const Vec3 &outwardNormal) {
        // true if ray is outside sphere
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    // Checks if Ray hits the Hittable object between a t value of t_min and t_max. Stores the results in HitRecord rec
    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const = 0;
    static const bool NO_HIT = false;
};

#endif