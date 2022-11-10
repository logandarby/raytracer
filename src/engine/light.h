#ifndef _LIGHT_H
#define _LIGHT_H

#include "../pch.h"

#include "material.h"

class DiffuseLight : public Material{
public:
    DiffuseLight(const Color c) :
        m_emitColor{c}
    {}

    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const override {
        (void)in;
        (void)rec;
        (void)attenuation;
        (void)scattered;
        return false;
    }

    virtual Color emmitted() const override {
        return m_emitColor;
    }
private:
    Color m_emitColor;
};

#endif