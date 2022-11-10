#ifndef _BVH_NODE_H
#define _BVH_NODE_H

#include "common/pch.h"

#include "../hittable.h"
#include "boundingbox.h"

class HittableList;

class BVHNode : public Hittable {
public:

    BVHNode(const HittableList &hitlist);
    BVHNode(const HittableList &hitlist, const size_t start, const size_t end);

    virtual bool hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const override;
    virtual bool boundingBox(BoundingBox &outputBox) const override;

private:
    std::shared_ptr<Hittable> m_left;
    std::shared_ptr<Hittable> m_right;
    BoundingBox m_boundingbox;
};

#endif