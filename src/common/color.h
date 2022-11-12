#ifndef _COLOR_H
#define _COLOR_H

#include "pch.h"

#include "vec3.h"

typedef Vec3 Color;

const Color V_BLACK{0, 0, 0};
const Color V_WHITE{1, 1, 1};
const Color V_RED{1, 0, 0};
const Color V_GREEN{0, 1, 0};
const Color V_BLUE{0, 0, 1};

void writeColor(std::ostream& out, Color pixel, const int samplesPerPixel);
// Averages the color over the samples, and gamma corrects
Color normalizePixel(const Color pixel, const int samplesPerPixel);
// Converts from pixel space from [0, 1] to [0, 255)
Color convertToRGB(Color pixel);

Color randomColor();
Color randomColor(double min, double max);

#endif