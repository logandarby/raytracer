#ifndef ___UTIL_H
#define ___UTIL_H

#include <limits>
#include <cmath>
#include <random>

#include "vec3.h"

const double DBL_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double degreesToRadians(const double deg);

// Returns random number in [0, 1)
double randomDouble();

// Returns random number in [min, max)
double randomDouble(const double min, const double max);

Vec3d randomVector();

Vec3d randomVector(const double min, const double max);

Vec3d randomInUnitSphere();

Vec3d randomUnitVector();

#endif