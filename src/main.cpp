#include <iostream>

#include "color.h"
#include "vec3.h"
#include "engine/ray.h"

// eq for sphere is (P - C) · (P - C) = r^2
// solving substituting in for P(t) = At + B we get
// t^2 b · b + 2tb · (A - C) + (A - C) · (A - C) - r^2 = 0
// which is quadratic, so the sphere is hit when discriminant > 0
const double NO_SPHERE_HIT = -1.0;
double hitSphere(const Point &center, const double radius, const Ray &r) {
    const Vec3 ac = r.origin() - center;
    const double a = dot(r.direction(), r.direction());
    const double b = 2.0 * dot(r.direction(), ac);
    const double c = dot(ac, ac) - radius * radius;
    const double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return NO_SPHERE_HIT;
    }
    return (-b - sqrt(discriminant)) / (2.0 * a);
}

Color ray_color(const Ray& r) {
    // Place spere at (0, 0, -1)
    Point centerPoint{0, 0, -1};
    double t = hitSphere(centerPoint, 0.5, r);
    if (t > 0) {
        Vec3 normal = normalize(r.at(t) - centerPoint);
        // each component x will be -1 < x < 1
        return 0.5 * Color{normal.x() + 1, normal.y() + 1, normal.z() + 1};
    }
    
    // background gradient
    Vec3 unit_direction = normalize(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color{1.0, 1.0, 1.0} + t*Color{0.5, 0.7, 1.0};
}

int main() {

     // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalHeight = 1.0;

    Point origin{0, 0, 0};
    Vec3<double> horizontal{viewportWidth, 0, 0};
    Vec3<double> vertical{0, viewportHeight, 0};
    auto lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vec3<double>{0, 0, focalHeight};

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight-1; j >= 0; --j) {
	std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            double u = double(i) / (imageWidth - 1);
            double v = double(j) / (imageHeight - 1);
            Ray r{origin, lowerLeftCorner + u * horizontal + v * vertical - origin};
            Color pixel = ray_color(r);
            writeColor(std::cout, pixel);
        }
    }
    std::cerr << "\nDone\n";
}
