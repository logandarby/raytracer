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
