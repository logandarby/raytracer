#ifndef _AARECT_H
#define _AARECT_H

#include "hittable.h"

const double _AARECT_THICKNESS = 0.00001;

// A rentangle that spans in the XY directions
class XYRect : public Hittable{
public:
    XYRect(const double x1, const double x2, const double y1, const double y2, const double z, const std::shared_ptr<Material> material) :
        m_x1{x1}, m_x2{x2}, m_y1{y1}, m_y2{y2}, m_z{z}, m_matptr{material}
    {
        if (m_x1 > m_x2) {
            std::swap(m_x1, m_x2);
        }
        if (m_y1 > m_y2) {
            std::swap(m_y1, m_y2);
        }
    }

    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;

    virtual bool boundingBox(BoundingBox &outputBox) const override;

private:
    double m_x1, m_x2, m_y1, m_y2, m_z;
    std::shared_ptr<Material> m_matptr;
};

// A rentangle that spans in the YZ directions
class YZRect : public Hittable{
public:
    YZRect(const double y1, const double y2, const double z1, const double z2, const double x, const std::shared_ptr<Material> material) :
        m_y1{y1}, m_y2{y2}, m_z1{z1}, m_z2{z2}, m_x{x}, m_matptr{material}
    {
        if (m_y1 > m_y2) {
            std::swap(m_y1, m_y2);
        }
        if (m_z1 > m_z2) {
            std::swap(m_z1, m_z2);
        }
    }

    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;

    virtual bool boundingBox(BoundingBox &outputBox) const override;

private:
    double m_y1, m_y2, m_z1, m_z2, m_x;
    std::shared_ptr<Material> m_matptr;
};

// A rentangle that spans in the XZ directions
class XZRect : public Hittable{
public:
    XZRect(const double x1, const double x2, const double z1, const double z2, const double y, const std::shared_ptr<Material> material) :
        m_x1{x1}, m_x2{x2}, m_z1{z1}, m_z2{z2}, m_y{y}, m_matptr{material}
    {
        if (m_x1 > m_x2) {
            std::swap(m_x1, m_x2);
        }
        if (m_z1 > m_z2) {
            std::swap(m_z1, m_z2);
        }
    }

    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;

    virtual bool boundingBox(BoundingBox &outputBox) const override;

private:
    double m_x1, m_x2, m_z1, m_z2, m_y;
    std::shared_ptr<Material> m_matptr;
};


#endif