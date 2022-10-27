#include <iostream>

#include "color.h"
#include "util.h"
#include "engine/camera.h"
#include "engine/ray.h"
#include "engine/sphere.h"
#include "engine/hittableList.h"

Color ray_color(const Ray& r, const Hittable& scene, const int depth) {

    if (depth <= 0) {
        return Color{0, 0, 0};
    }

    HitRecord rec{};
    if (scene.hit(r, 0.001, DBL_INFINITY, rec)) {
        Point target = rec.p + rec.normal + randomUnitVector();
        return 0.5 * ray_color(Ray{rec.p, target - rec.p}, scene, depth - 1);
    }

    // background gradient
    Vec3<double> unit_direction = normalize(r.direction());
    const double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color{1.0, 1.0, 1.0} + t*Color{0.5, 0.7, 1.0};
}

int main() {
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 20;
    const int maxDepth = 20;

    // Scene
    HittableList scene{};
    scene.add(make_shared<Sphere>(Point{0, 0, -1}, 0.5));
    scene.add(make_shared<Sphere>(Point{0, -100.5, -1}, 100));

    // Camera
    Camera camera;

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight-1; j >= 0; --j) {
	    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            // antialiasing
            Color pixel{0, 0, 0};
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = double(i + randomDouble()) / (imageWidth - 1);
                double v = double(j + randomDouble()) / (imageHeight - 1);
                Ray r = camera.getRay(u, v);
                pixel += ray_color(r, scene, maxDepth);
            }
            writeColor(std::cout, pixel, samplesPerPixel);
        }
    }
    std::cerr << "\nDone\n";
}
