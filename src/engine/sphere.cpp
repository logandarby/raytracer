#include "../pch.h"

#include "sphere.h"
#include "../util/util.h"
#include "../util/debug.h"

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
    getUV(outwardNormal, rec.u, rec.v);
    return true;
}

bool Sphere::boundingBox(BoundingBox &outputBox) const {
    outputBox = BoundingBox{
        m_center - m_radius * Vec3{1, 1, 1},
        m_center + m_radius * Vec3{1, 1, 1}
    };
    return true;
}

// Gets the surface coordinates (in polar) and stores them in u, v
// as well as normalizing u, v to be in [0, 1]
// P must be a point on the unit sphere centered at the origin
// u represents theta up from the -Y axis (max of pi radians)
// v represents the phi around the Y axis (max of 2pi radians)
void Sphere::getUV(const Point &p, double &u, double &v) const {
    debugAssert(p.x() * p.x() + p.y() * p.y() + p.z() * p.z() == 1);

    const double phi = std::atan2(-p.z(), p.x()) + PI;
    const double theta = std::acos(-p.y());
    // normalize
    u = phi / (2 * PI);
    v = theta / PI;
}