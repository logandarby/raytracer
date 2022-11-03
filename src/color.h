#ifndef _COLOR_H
#define _COLOR_H

#include "vec3.h"

#include <ostream>

typedef Vec3 Color;

const Color V_BLACK{0, 0, 0};
const Color V_WHITE{1, 1, 1};
const Color V_RED{1, 0, 0};
const Color V_GREEN{0, 1, 0};
const Color V_BLUE{0, 0, 1};

void writeColor(std::ostream& out, Color pixel, const int samplesPerPixel);

Color randomColor();
Color randomColor(double min, double max);

#endif