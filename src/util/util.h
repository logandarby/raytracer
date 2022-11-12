#ifndef ___UTIL_H
#define ___UTIL_H

#include "common/pch.h"

#include "common/vec3.h"

const double DBL_INFINITY = std::numeric_limits<double>::infinity();
const float FLT_INFINITY = std::numeric_limits<float>::infinity();
const int INT_INFINITY = INT_MAX;

const double PI = 3.1415926535897932385;

double degreesToRadians(const double deg);

// Very fast RNG, but not accurate.
// Returns random number in [0, 1)
double fastRandomDouble();

double fastRandomDouble(const double min, const double max);

// Returns random number in [0, 1)
double randomDouble();

// Returns random number in [min, max)
double randomDouble(const double min, const double max);

// Return random int in [min, max]
int randomInt(const int min, const int max);

// Super fast inverse square root
float fastInvSqrt(float number);

#endif