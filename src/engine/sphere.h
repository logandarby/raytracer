#ifndef _SPHERE_H
#define _SPHERE_H

#include "hittable.h"
#include "material.h"
#include "BVH/boundingbox.h"

class Sphere : public Hittable {
public:
    Sphere() :
        m_center{0, 0, -1},
        m_radius{0.5},
        m_material{std::make_shared<Lambertian>(Color{0, 0, 0})}
    {}
    Sphere(Point center, double radius, std::shared_ptr<Material> m) :
        m_center{center}, m_radius{radius}, m_material{m}
    {}

    // Checks if Ray hits the Hittable object between a t value of t_min and t_max. Stores the results in HitRecord rec
    bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;
    // Stores the axis-aligned boundingbox in outputBox
    bool boundingBox(BoundingBox &outputBox) const override;
    // Gets the surface coordinates (in polar) and stores them in u, v.
    // P must be a point on the unit sphere centered at the origin
    // u represents theta up from the -Y axis (max of pi radians)
    // v represents the phi around the Y axis (max of 2pi radians)
    void getUV(const Point &p, double &u, double &v) const;
private:
    Point m_center;
    double m_radius;
    std::shared_ptr<Material> m_material;
};

#endif