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

double randomDouble(const int min, const int max) {
    return min + (max-min) * randomDouble();
}

int randomInt(const int min, const int max) {
    return static_cast<int>(randomDouble(min, max + 1));
}

static unsigned long x=123456789, y=362436069, z=521288629;

double fastRandomDouble(void) {  //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return (double) z / ULONG_MAX;
}

double fastRandomDouble(const double min, const double max) {
    return min + (max-min) * fastRandomDouble();
}