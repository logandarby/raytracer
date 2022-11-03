#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "hittable.h"
#include "../color.h"
#include "../util/util.h"

struct Ray;

class Material {
public:
    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const = 0;
    virtual Color emmitted() const {
        return V_BLACK;
    }
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

class Dielectric : public Material {
public:
    Dielectric(const double indexOfRefraction) : m_ir{indexOfRefraction} {}

    virtual bool scatter(
        const Ray &in, const HitRecord &rec, Color &attenuation, Ray &scattered
    ) const override {
        const double refractRatio = (rec.frontFace) ? 1.0/m_ir : m_ir;
        const Vec3 unitDir = normalize(in.direction());

        const double costheta = fmin(dot(-unitDir, rec.normal), 1.0);
        const double sintheta = sqrt(1.0 - costheta*costheta);

        const bool cannotRefract = refractRatio * sintheta > 1.0;
        Vec3 direction;
        if (cannotRefract || reflectance(costheta, refractRatio) > fastRandomDouble()) {
            // Total internal reflection
            direction = reflect(unitDir, rec.normal);
        } else {
            direction = refract(unitDir, rec.normal, refractRatio);
        }

        scattered = Ray{rec.p, direction};
        attenuation = Color{1.0, 1.0, 1.0};
        return true;
    }
private:
    double m_ir; // index of refraction;

    static double reflectance(const double cosine, const double refIdx) {
        // Use Schlick's approximation for reflectance.
        double r0 = (1-refIdx) / (1+refIdx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

#endif