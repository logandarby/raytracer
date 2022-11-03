#include "aarect.h"

bool XYRect::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    const double t = (m_z - r.origin().z()) / r.direction().z(); //z-intersect 
    if ((t < t_min) || (t > t_max))
        return false;

    const double x_intersect = r.at(t).x();
    const double y_intersect = r.at(t).y();

    if (m_x1 > x_intersect ||
        m_x2 < x_intersect ||
        m_y1 > y_intersect ||
        m_y2 < y_intersect)
        return false;

    rec.p = r.at(t);
    rec.materialPtr = m_matptr;
    rec.t = t;
    Vec3 outwardNormal{0, 0, 1};
    rec.setFaceNormal(r, outwardNormal);
    return true;
}

bool XYRect::boundingBox(BoundingBox &outputBox) const {
    outputBox = BoundingBox{Point{m_x1, m_y1, m_z-_AARECT_THICKNESS}, Point{m_x2, m_y2, m_z+_AARECT_THICKNESS}};
    return true;
}


bool YZRect::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    const double t = (m_x - r.origin().x()) / r.direction().x(); //x-intersect 
    if ((t < t_min) || (t > t_max))
        return false;

    const double y_intersect = r.at(t).y();
    const double z_intersect = r.at(t).z();

    if (m_z1 > z_intersect ||
        m_z2 < z_intersect ||
        m_y1 > y_intersect ||
        m_y2 < y_intersect)
        return false;

    rec.p = r.at(t);
    rec.materialPtr = m_matptr;
    rec.t = t;
    Vec3 outwardNormal{1, 0, 0};
    rec.setFaceNormal(r, outwardNormal);
    return true;
}

bool YZRect::boundingBox(BoundingBox &outputBox) const {
    outputBox = BoundingBox{Point{m_x-_AARECT_THICKNESS, m_y1, m_z1}, Point{m_x+_AARECT_THICKNESS, m_y2, m_z2}};
    return true;
}


bool XZRect::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    const double t = (m_y - r.origin().y()) / r.direction().y(); //y-intersect 
    if ((t < t_min) || (t > t_max))
        return false;

    const double x_intersect = r.at(t).x();
    const double z_intersect = r.at(t).z();

    if (m_x1 > x_intersect ||
        m_x2 < x_intersect ||
        m_z1 > z_intersect ||
        m_z2 < z_intersect)
        return false;

    rec.p = r.at(t);
    rec.materialPtr = m_matptr;
    rec.t = t;
    Vec3 outwardNormal{0, 1, 0};
    rec.setFaceNormal(r, outwardNormal);
    return true;
}

bool XZRect::boundingBox(BoundingBox &outputBox) const {
    outputBox = BoundingBox{Point{m_x1, m_y-_AARECT_THICKNESS, m_z1}, Point{m_x2, m_y+_AARECT_THICKNESS, m_z2}};
    return true;
}
