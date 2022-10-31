#include "sphere.h"

// eq for sphere is (P - C) · (P - C) = r^2
// solving substituting in for P(t) = At + B we get
// t^2 b · b + 2tb · (A - C) + (A - C) · (A - C) - r^2 = 0
// which is quadratic, so the sphere is hit when discriminant > 0
// This eq is simplified a bit too
bool Sphere::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    const Vec3 ac = r.origin() - m_center;
    const double a = r.direction().length_sqr();
    const double half_b = dot(r.direction(), ac);
    const double c = ac.length_sqr() - m_radius * m_radius;

    const double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return NO_HIT;
    const double sqrtd = sqrt(discriminant);
    
    // Check if either root is inbound
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) {
            return NO_HIT;
        }
    }

    rec.t = root;
    rec.p = r.at(root);
    rec.materialPtr = m_material;
    const Vec3 outwardNormal = (rec.p - m_center) / m_radius;
    rec.setFaceNormal(r, outwardNormal);
    return true;
}

bool Sphere::boundingBox(BoundingBox &outputBox) const {
    outputBox = BoundingBox{
        m_center - m_radius * Vec3{1, 1, 1},
        m_center + m_radius * Vec3{1, 1, 1}
    };
    return true;
}