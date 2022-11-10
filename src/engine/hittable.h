#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "common/pch.h"

#include "ray.h"
#include "bvh/boundingbox.h"

class Material;
struct HitRecord {
    Point p;        // intersection point
    Vec3 normal;    // surface normal (faces against incident ray)
    double t;       // ray parameter that gives point p
    double u, v;    // surface coordinates
    std::shared_ptr<Material> materialPtr;  // material
    bool frontFace; // true if ray hit the front-face of the object

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
    // Stores the objects axis-aligned bounding box in outputBox
    virtual bool boundingBox(BoundingBox &outputBox) const = 0;
    static const bool NO_HIT = false;
};

#endif