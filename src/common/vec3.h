#ifndef ___VEC3_H
#define ___VEC3_H

#include "pch.h"

class Vec3 {
public:
    Vec3() {}
    Vec3(const double a, const double b, const double c) {
        e[0] = a;
        e[1] = b;
        e[2] = c;
    }
    Vec3(const double v3[3]) {
        e[0] = v3[0];
        e[1] = v3[1];
        e[2] = v3[2];
    }
    Vec3(const float v3[3]) {
        e[0] = (double) v3[0];
        e[1] = (double) v3[1];
        e[2] = (double) v3[2];
    }
    
    double const &x() const { return e[0]; }
    double const &y() const { return e[1]; }
    double const &z() const { return e[2]; }

    double &x() { return e[0]; }
    double &y() { return e[1]; }
    double &z() { return e[2]; }

    double *data() { return &e[0]; }
    double const *data() const { return &e[0]; }

    Vec3 operator-();
    Vec3 operator-() const;
    // double operator[](const int i);
    double const &operator[](const int i) const;
    double &operator[](const int i);

    Vec3& operator+=(const Vec3 &v);
    Vec3& operator-=(const Vec3 &v);
    Vec3& operator*=(const double t);
    Vec3& operator/=(const double t);

    bool operator==(const Vec3 &v) const;

    double length() const;
    double length_sqr() const;
    bool nearZero() const;

    static Vec3 randomVector();
    static Vec3 randomVector(const double min, const double max);
    // For circular diffusion
    static Vec3 randomInUnitSphere();
    // For uninform diffusion
    static Vec3 randomInHemisphere(const Vec3 &normal);
    // For true lambertian diffusion (ideal)
    static Vec3 randomUnitVector();
    static Vec3 randomInUnitDisk();
private:
    double e[3] = {0, 0, 0};
};

std::ostream& operator<<(std::ostream &out, const Vec3 &v);

Vec3 operator+(const Vec3 &u, const Vec3 &v);
Vec3 operator-(const Vec3 &u, const Vec3 &v);
Vec3 operator*(const Vec3 &u, const Vec3 &v);
Vec3 operator*(double t, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double t);
Vec3 operator/(Vec3 v, double t);

double dot(const Vec3 &u, const Vec3 &v);
Vec3 cross(const Vec3 &u, const Vec3 &v);
Vec3 normalize(Vec3 v);

Vec3 reflect(const Vec3 &v, const Vec3 &normal);
/*  Note that refractionratio is the ratio between the refraction indices of where the
    ray is coming from, over where the ray is going */
Vec3 refract(const Vec3 &v, const Vec3 &normal, const double refractionratio);

typedef Vec3 Point;

const Vec3 V_UNIT{1, 1, 1};
const Vec3 V_ORIGIN{0, 0, 0};

#endif