#include "vec3.h"
#include "util.h"

Vec3 Vec3::operator-() {
    e[1] *= -1;
    e[2] *= -1;
    e[0] *= -1;
    return *this;
}

Vec3 Vec3::operator-() const {
    return Vec3{-1 * e[0], -1 * e[1], -1 * e[2]};
}

double Vec3::operator[](const int i) const {
    if (i < 0 || i > 2) {
        throw std::out_of_range("Index of Vec3 must be between 0 and 2 inclusive");
    }
    return e[i];
}

double Vec3::operator[](const int i) {
    if (i < 0 || i > 2) {
        throw std::out_of_range("Index of Vec3 must be between 0 and 2 inclusive");
    }
    return e[i];
}

Vec3& Vec3::operator+=(const Vec3 &v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

Vec3& Vec3::operator-=(const Vec3 &v) {
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

Vec3& Vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const double t) {
    if (t == 0) {
        throw std::runtime_error("Math error: Vec3 may not be divided by scalar 0");
    }
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

double Vec3::length() const {
    return std::sqrt(length_sqr());
}

double Vec3::length_sqr() const {
    return e[0] * e[0] + e[1] * e[1]  + e[2] * e[2];
}

bool Vec3::nearZero() const {
    const double s = 1e-8;
    return fabs(e[0]) < s && fabs(e[1]) < s && fabs(e[2]) < s;
}

Vec3 Vec3::randomVector() {
    return Vec3{randomDouble(), randomDouble(), randomDouble()};
}

Vec3 Vec3::randomVector(const double min, const double max) {
    return Vec3{randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
}

Vec3 Vec3::randomInUnitSphere() {
    while(true) {
        auto target = randomVector(-1, 1);
        if (target.length_sqr() > 1) continue;
        return target;  
    }
}

Vec3 Vec3::randomUnitVector() {
    return normalize(randomInUnitSphere());
}

Vec3 Vec3::randomInHemisphere(const Vec3 &normal) {
    Vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0) {
        return inUnitSphere;
    }
    return -inUnitSphere;
}

std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t * v[0], t * v[1], t * v[2]);
}

Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

double dot(const Vec3 &u, const Vec3 &v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

Vec3 normalize(Vec3 v) {
    return v / v.length();
}

Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*dot(v, n)*n;
}