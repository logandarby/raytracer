#ifndef _VEC3_H
#define _VEC3_H

#include <ostream>
#include <array>
#include <cmath>

template <class T>
class Vec3 {
public:
    Vec3() : 
        e{ T{}, T{}, T{} }
    {}
    Vec3(T a, T b, T c) :
        e{a, b, c}
    {}
    
    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    Vec3<T> operator-() {
        e[1] *= -1;
        e[2] *= -1;
        e[0] *= -1;
        return *this;
    }
    T operator[](const int i) const {
        if (i < 0 || i > 2) {
            throw std::out_of_range("Index of Vec3<T> must be between 0 and 2 inclusive");
        }
        return e[i];
    }

    T& operator[](const int i) {
        if (i < 0 || i > 2) {
            throw std::out_of_range("Index of Vec3<T> must be between 0 and 2 inclusive");
        }
        return e[i];
    }

    Vec3<T>& operator+=(const Vec3<T> &v) {
        e[0] += v.x();
        e[1] += v.y();
        e[2] += v.z();
        return *this;
    }
    Vec3<T>& operator-=(const Vec3<T> &v) {
        e[0] -= v.x();
        e[1] -= v.y();
        e[2] -= v.z();
        return *this;
    }
    Vec3<T>& operator*=(const T t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    Vec3<T>& operator/=(const T t) {
        if (t == 0) {
            throw std::runtime_error("Math error: Vec3<T> may not be divided by scalar 0");
        }
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }

    T length() const {
        return std::sqrt(length_sqr());
    }
    T length_sqr() const {
        return e[0] * e[0] + e[1] * e[1]  + e[2] * e[2];
    }
private:
    std::array<T, 3> e;
};

template <typename T>
std::ostream& operator<<(std::ostream &out, const Vec3<T> &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

template <typename T>
Vec3<T> operator+(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3<T>(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

template <typename T>
Vec3<T> operator-(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3<T>(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3<T>(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

template <typename T>
Vec3<T> operator*(double t, const Vec3<T> &v) {
    return Vec3<T>(t * v[0], t * v[1], t * v[2]);
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &v, double t) {
    return t * v;
}

template <typename T>
Vec3<T> operator/(Vec3<T> v, double t) {
    return (1/t) * v;
}

template <typename T>
double dot(const Vec3<T> &u, const Vec3<T> &v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

template <typename T>
Vec3<T> cross(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3<T>(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

template <typename T>
Vec3<T> normalize(Vec3<T> v) {
    return v / v.length();
}

typedef Vec3<double> Point;
typedef Vec3<double> Direction;

#endif