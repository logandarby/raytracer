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

HittableList randomScene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -7; a < 7; a+=2) {
        for (int b = -7; b < 7; b +=2) {
            auto choose_mat = randomDouble();
            Point center(a + 0.9*randomDouble(), 0.2, b + 0.9*randomDouble());

            if ((center - Point(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = randomColor() * randomColor();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = randomColor(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    // Image
    const auto aspectRatio = 3.0 / 2.0;
    const int imageWidth = 1200;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 200;
    const int maxDepth = 50;

    // Camera
    const Point lookfrom{13, 2, 3};
    const Point lookat{0, 0, 0};
    const Point vup{0, 1, 0};
    const double fov = 20;
    const double distanceToFocus = 10;
    const double aperture = 0.1;
    Camera camera{aspectRatio, lookfrom, lookat, vup, fov, aperture, distanceToFocus};

    // Scene
    HittableList scene = randomScene();

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
