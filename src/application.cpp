#include "application.h"
#include "engine/camera.h"
#include "engine/hittableList.h"
#include "engine/bvh.h"
#include "scene.h"
#include "graphics/PPMstream.h"


void Application::Run() {
    m_view.Create(m_renderOptions);
    m_view.Run();
}

void Application::Render() {
    // Image
    const auto aspectRatio = getAspectRatioValue.at(m_renderOptions->aspectRatio);
    const int imageWidth = m_renderOptions->imageWidth;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = m_renderOptions->samplesPerPixel;
    const int maxDepth = m_renderOptions->maxDepth;

    // Camera
    const Point lookfrom = m_renderOptions->lookFrom;
    const Point lookat = m_renderOptions->lookAt;
    const Point vup{0, 1, 0};
    const double fov = m_renderOptions->fov;
    const double distanceToFocus = m_renderOptions->focusDistance;
    const double aperture = m_renderOptions->aperture;
    Camera camera{aspectRatio, lookfrom, lookat, vup, fov, aperture, distanceToFocus};

    HittableList scene = createScene();
    
    Hittable *finalscene = &scene;

    if(m_USE_BVH) {
        BVHNode sceneObjectTree{scene};
        finalscene  = &sceneObjectTree;
    }

    // Render

    m_renderer = Renderer{imageWidth, imageHeight, samplesPerPixel, maxDepth};

    auto start = std::chrono::steady_clock::now();

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    m_renderer.render(*finalscene, camera);   // main render

    auto end = std::chrono::steady_clock::now();

    std::cerr << "Time Elapsed in minutes: "
        << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
        << " minutes\n";
    std::cerr << "OR\n";
    std::cerr << "Time Elapsed in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " seconds\n";
}