#include "color.h"
#include "util/util.h"

Color convertToRGB(const Color pixel) {

    double r = static_cast<int>(256 * std::clamp(pixel.x(), 0.0, 0.999));
    double g = static_cast<int>(256 * std::clamp(pixel.y(), 0.0, 0.999));
    double b = static_cast<int>(256 * std::clamp(pixel.z(), 0.0, 0.999));

    return Color{r, g, b};
}

Color normalizePixel(const Color pixel, const int samplesPerPixel) {
    double r = pixel.x();
    double g = pixel.y();
    double b = pixel.z();

    // average samples and gamma correct for gamma 2
    const double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    return Color{r, g, b};
}

void writeColor(std::ostream& out, const Color pixel, const int samplesPerPixel) {

    const Color rgbPixel = convertToRGB(normalizePixel(pixel, samplesPerPixel));

    out << rgbPixel.x() << ' '
        << rgbPixel.y() << ' '
        << rgbPixel.z() << std::endl;
}

Color randomColor() {
    return Color{fastRandomDouble(), fastRandomDouble(), fastRandomDouble()};
}

Color randomColor(const double min, const double max) {
    return Color{fastRandomDouble(min, max), fastRandomDouble(min, max), fastRandomDouble(min, max)};
}
