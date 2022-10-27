#ifndef _COLOR_H
#define _COLOR_H

#include "vec3.h"

#include <ostream>

typedef Vec3 Color;

void writeColor(std::ostream& out, Color pixel, const int samplesPerPixel);

Color randomColor();
Color randomColor(double min, double max);

#endif