#ifndef _SPHERE_H
#define _SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
public:
    Sphere() : m_center{0, 0, -1}, m_radius{0.5} {}
    Sphere(Point center, double radius) : m_center{center}, m_radius{radius} {}

    // Checks if Ray hits the Hittable object between a t value of t_min and t_max. Stores the results in HitRecord rec
    bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;
private:
    Point m_center;
    double m_radius;
};

#endif