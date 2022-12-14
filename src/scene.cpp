#include "scene.h"
#include "common/color.h"
#include "engine/material.h"
#include "engine/sphere.h"
#include "engine/aarect.h"
#include "engine/light.h"

HittableList randomScene();

HittableList createScene() {
    // Scene
    HittableList scene = randomScene();
    auto lightmat = make_shared<DiffuseLight>(Color{4, 4, 4});
    auto lightrectxy = make_shared<XYRect>(3, 5, 1, 3, -2, lightmat);
    auto lightrectxz = make_shared<XZRect>(-1, 1, -1, 1, 4, lightmat);
    auto lightrectyz = make_shared<YZRect>(1, 3, -1, 1, -5, lightmat);
    scene.add(lightrectxy);
    scene.add(lightrectxz);
    scene.add(lightrectyz);
    return scene;
}

HittableList randomScene() {
    HittableList world;

    auto check = make_shared<Checkered>();
    auto ground_material = make_shared<Lambertian>(check);
    // auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -7; a < 7; a+=2) {
        for (int b = -7; b < 7; b +=2) {
            auto choose_mat = fastRandomDouble();
            Point center(a + 0.9*fastRandomDouble(), 0.2, b + 0.9*fastRandomDouble());

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
                    auto fuzz = fastRandomDouble(0, 0.5);
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