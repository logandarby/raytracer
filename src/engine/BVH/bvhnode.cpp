#include "bvhnode.h"
#include "../../util/util.h"
#include "../../util/debug.h"
#include "../hittableList.h"

#include <algorithm>

enum {X = 0, Y, Z};

bool boxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, const int axis) {
    BoundingBox temp1;
    BoundingBox temp2;

    debugAssert(a->boundingBox(temp1) && b->boundingBox(temp2));

    return temp1.min()[axis] < temp2.min()[axis];
}

bool boxCompareZ(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 0);
}

bool boxCompareY(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 1);
}

bool boxCompareX(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return boxCompare(a, b, 2);
}

BVHNode::BVHNode(const HittableList &hitlist)
    : BVHNode{hitlist, 0, hitlist.m_objects.size()}
{}

BVHNode::BVHNode(const HittableList &hitlist, const size_t start, const size_t end) {
    auto objects = hitlist.m_objects;
    const size_t size = end - start;

    const int axis = randomInt(0, 2);
    const auto compareFunc = 
          (axis == X) ? boxCompareX
        : (axis == Y) ? boxCompareY
        : boxCompareZ;

    // sort objects over random axis

    if (size == 1) {
        m_left = objects[start];
        m_right = objects[start];
    } else if (size == 2) {
        m_left = objects[start];
        m_right = objects[start + 1];
        if (!compareFunc(m_left, m_right)) {
            std::swap(m_left, m_right);
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, compareFunc);
        const size_t midpoint = start + size / 2;
        m_left = make_shared<BVHNode>(hitlist, start, midpoint);
        m_right = make_shared<BVHNode>(hitlist, midpoint, end);
    }

    BoundingBox boxLeft;
    BoundingBox boxRight;

    assert(m_left->boundingBox(boxLeft) && m_right->boundingBox(boxRight));

    m_boundingbox = BoundingBox::combineBoxes(boxLeft, boxRight);
}

bool BVHNode::boundingBox(BoundingBox &outputBox) const {
    outputBox = m_boundingbox;
    return true;
}

bool BVHNode::hit(const Ray &r, const double t_min, const double t_max, HitRecord &rec) const {
    if (!m_boundingbox.hit(r, t_min, t_max)) {
        return false;
    }

    const bool hitLeft = m_left->hit(r, t_min, t_max, rec);
    const bool hitRight = m_right->hit(r, t_min, hitLeft ? rec.t : t_max, rec);
    return hitLeft || hitRight;

}

