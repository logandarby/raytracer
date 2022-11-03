#include "color.h"
#include "util/util.h"
#include <algorithm>

void writeColor(std::ostream& out, const Color pixel, const int samplesPerPixel) {

    double r = pixel.x();
    double g = pixel.y();
    double b = pixel.z();

    // average samples and gamma correct for gamma 2
    const double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << std::endl;
}

Color randomColor() {
    return Color{fastRandomDouble(), fastRandomDouble(), fastRandomDouble()};
}

Color randomColor(const double min, const double max) {
    return Color{fastRandomDouble(min, max), fastRandomDouble(min, max), fastRandomDouble(min, max)};
}
