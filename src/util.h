#ifndef _UTIL_H
#define _UTIL_H

#include <limits>
#include <cmath>
#include <random>

const double DBL_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

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

#endif