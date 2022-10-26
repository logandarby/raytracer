#ifndef _COLOR_H
#define _COLOR_H

#include "vec3.h"

#include <ostream>

typedef Vec3<double> Color;

void writeColor(std::ostream& out, Color pixel);

#endif