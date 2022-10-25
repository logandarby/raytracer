#include "color.h"

void writeColor(std::ostream& out, const Color pixel) {
    out << static_cast<int>(255.999 * pixel.x()) << ' '
        << static_cast<int>(255.999 * pixel.y()) << ' '
        << static_cast<int>(255.999 * pixel.z()) << std::endl;
}
