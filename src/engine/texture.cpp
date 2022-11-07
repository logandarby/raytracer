#include "texture.h"

Color SolidColor::value(const double u, const double v, const Point &p) const {
    (void)u;
    (void)v;
    (void)p;
    return m_color;
}

Color Checkered::value(const double u, const double v, const Point &p) const {
    (void)u;
    (void)v;
    const double sine = sin(m_size * p.x()) * sin(m_size * p.y()) * sin(m_size * p.z());
    if (sine > 0) return m_c1;
    else return m_c2;
}