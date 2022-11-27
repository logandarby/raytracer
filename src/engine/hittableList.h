#ifndef _HITTABLE_LIST_H
#define _HITTABLE_LIST_H

#include "common/pch.h"

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void add(shared_ptr<Hittable> object) { m_objects.push_back(object); }
    void clear() { m_objects.clear(); }
    int size() { return m_objects.size(); }

    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;
    virtual bool boundingBox(BoundingBox &outputBox) const override;

private:
    std::vector<shared_ptr<Hittable>> m_objects;
    friend class BVHNode;
};

#endif