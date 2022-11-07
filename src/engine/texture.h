#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "color.h"

class Texture {
public:
    // Given a uv-surface coordinate, and the surface point p, a color is returned
    virtual Color value(const double u, const double v, const Point &p) const = 0;
};


class SolidColor : public Texture {
public:
    SolidColor(const Color c = V_WHITE) :
        m_color{c}
    {}

    virtual Color value(const double u, const double v, const Point &p) const override;
private:
    const Color m_color;
};


class Checkered : public Texture {
public:
    Checkered(const Color c1 = V_WHITE, const Color c2 = V_BLACK, const double size = 10) :
        m_c1{c1}, m_c2{c2}, m_size{size}
    {}

    virtual Color value(const double u, const double v, const Point &p) const override;
private:
    const Color m_c1;
    const Color m_c2;
    const double m_size;
};

#endif