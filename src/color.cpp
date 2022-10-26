#include "color.h"
#include <algorithm>

void writeColor(std::ostream& out, const Color pixel, const int samplesPerPixel) {

    double r = pixel.x();
    double g = pixel.y();
    double b = pixel.z();

    const double scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << std::endl;
}
