#include "common/pch.h"

#include "common/renderOptions.h"
#include "util/util.h"
#include "engine/camera.h"
#include "engine/bvh.h"
#include "engine/renderer.h"
#include "scene.h"

const bool USE_BVH = false;

#include "graphics/view.h"

int main(int, char**) {

    auto renderOptions = make_shared<RenderOptions>();
    View view;
    view.Create(renderOptions);
    view.Run();
    return EXIT_SUCCESS;








    // Image
    const auto aspectRatio = 3.0 / 2.0;
    const int imageWidth = 300;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 30;
    const int maxDepth = 10;

    // Camera
    const Point lookfrom{13, 2, 3};
    const Point lookat{0, 0, 0};
    const Point vup{0, 1, 0};
    const double fov = 25;
    const double distanceToFocus = 10;
    const double aperture = 0.1;
    Camera camera{aspectRatio, lookfrom, lookat, vup, fov, aperture, distanceToFocus};

    HittableList scene = createScene();
    
    Hittable *finalscene = &scene;

    if(USE_BVH) {
        BVHNode sceneObjectTree{scene};
        finalscene  = &sceneObjectTree;
    }

    // Render

    Renderer renderer{imageWidth, imageHeight, samplesPerPixel, maxDepth};

    auto start = std::chrono::steady_clock::now();

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    renderer.render(*finalscene, camera);   // main render

    auto end = std::chrono::steady_clock::now();

    std::cerr << "Time Elapsed in minutes: "
        << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
        << " minutes\n";
    std::cerr << "OR\n";
    std::cerr << "Time Elapsed in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " seconds\n";

    return EXIT_SUCCESS;
}
