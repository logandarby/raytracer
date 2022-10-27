#include "util.h"

double degreesToRadians(const double deg) {
    return deg * PI / 180.0;
}

// Returns random number in [0, 1)
double randomDouble() {
    static std::uniform_real_distribution<double> distribution{0.0, 1.0};
    static std::mt19937 generator;
    return distribution(generator);
}

// Returns random number in [min, max)
double randomDouble(const double min, const double max) {
    return min + (max-min) * randomDouble();
}

Vec3d randomVector() {
    return Vec3d{randomDouble(), randomDouble(), randomDouble()};
}

Vec3d randomVector(const double min, const double max) {
    return Vec3d{randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
}

Vec3d randomInUnitSphere() {
    while(true) {
        auto target = randomVector(-1, 1);
        if (target.length_sqr() > 1) continue;
        return target;  
    }
}

Vec3d randomUnitVector() {
    return normalize(randomInUnitSphere());
}

Vec3d randomInHemisphere(const Vec3d &normal) {
    Vec3d inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0) {
        return inUnitSphere;
    }
    return -inUnitSphere;
}
