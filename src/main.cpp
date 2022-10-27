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
        Ray scattered;
        Color attenuation;
        if (rec.materialPtr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, scene, depth - 1);
        }
        return Color{0, 0, 0};
    }

    // background gradient
    Vec3 unit_direction = normalize(r.direction());
    const double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color{1.0, 1.0, 1.0} + t*Color{0.5, 0.7, 1.0};
}

int main() {
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    // Camera
    const Point lookfrom{-2, 2, 1};
    const Point lookat{0, 0, -1};
    const Point vup{0, 1, 0};
    const double fov = 40;
    const double distanceToFocus = (lookfrom - lookat).length();
    const double aperture = 0.8;
    Camera camera{aspectRatio, lookfrom, lookat, vup, fov, aperture, distanceToFocus};

    // Scene
    HittableList scene{};
    auto materialGround = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    auto materialCenter = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialLeft   = make_shared<Dielectric>(1.5);
    auto materialRight  = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.5);

    scene.add(make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, materialGround));
    scene.add(make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, materialCenter));
    scene.add(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, materialLeft));
    scene.add(make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, materialRight));

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
