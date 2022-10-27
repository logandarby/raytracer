#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "hittable.h"
#include "../color.h"
#include "../util.h"

struct Ray;

class Material {
public:
    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const Color &a) : m_albedo{a} {}

    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const override {
        (void)in;
        Point scatterDirection = rec.normal + Vec3::randomUnitVector();

        // Catch degenerate scatter
        if (scatterDirection.nearZero()) {
            scatterDirection = rec.normal;
        }

        scattered = Ray{rec.p, scatterDirection};
        attenuation = m_albedo;
        return true;
    }
private:
    Color m_albedo;
};

class Metal : public Material {
public:
    Metal(const Color &a, const double fuzz) : m_albedo{a}, m_fuzz{fuzz} {};

    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const override {
        Vec3 refleced = reflect(normalize(in.direction()), rec.normal);
        scattered = Ray{rec.p, refleced + m_fuzz*Vec3::randomInUnitSphere()};
        attenuation = m_albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
private:
    Color m_albedo;
    double m_fuzz;
};

#endif