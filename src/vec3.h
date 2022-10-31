#ifndef ___VEC3_H
#define ___VEC3_H

#include <ostream>
#include <array>
#include <cmath>

class Vec3 {
public:
    Vec3() : 
        e{ 0, 0, 0 }
    {}
    Vec3(double a, double b, double c) :
        e{a, b, c}
    {}
    
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-();
    Vec3 operator-() const;
    double operator[](const int i);
    double operator[](const int i) const;

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
    std::array<double, 3> e;
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