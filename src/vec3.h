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
    double operator[](const int i) const;
    double operator[](const int i);

    Vec3& operator+=(const Vec3 &v);
    Vec3& operator-=(const Vec3 &v);
    Vec3& operator*=(const double t);
    Vec3& operator/=(const double t);

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

typedef Vec3 Point;

#endif