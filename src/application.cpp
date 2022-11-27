#include "application.h"
#include "engine/camera.h"
#include "engine/hittableList.h"
#include "engine/bvh.h"
#include "scene.h"
#include "common/colorStreams/ppmStream.h"

#define BIND_CLASS_FN(eventFunc) std::bind(&Application::eventFunc, this, std::placeholders::_1)

Application::Application() : 
    m_renderOptions{std::make_shared<RenderOptions>()},
    m_view{},
    m_renderer{m_renderOptions->imageWidth, m_renderOptions->imageHeight}
{
    m_view.setEventCallback(BIND_CLASS_FN(onEvent));
}

void Application::Run() {
    m_view.Create(m_renderOptions);
    m_view.Run();
}

#include <cstdlib>
#include <unistd.h>

void Application::onButtonPress(ButtonPressEvent &e) {
    if (e.getButtonID() == "render") {
        stopRendering();
        m_renderThread = std::thread{Render, this};
    };
}

void Application::onWindowClose(WindowCloseEvent &e) {
    (void)e;
    stopRendering();
}

void Application::onFieldModify(FieldModifyEvent &e) {
    if (e.getFieldID() == "fieldOptionsModify") {
        stopRendering();
    }
}

void Application::onEvent(Event &e) {
    Event::dispatch<ButtonPressEvent>(e, BIND_CLASS_FN(onButtonPress));
    Event::dispatch<WindowCloseEvent>(e, BIND_CLASS_FN(onWindowClose));
    Event::dispatch<FieldModifyEvent>(e, BIND_CLASS_FN(onFieldModify));
}

void Application::stopRendering() {
    const std::lock_guard<std::mutex> lock{m_renderMutex};
    if(m_renderer.isRunning()) {
        m_renderer.stop();
    }
    if(m_renderThread.joinable())
        m_renderThread.join();
}

void Application::Render() {
    // Image
    const auto aspectRatio = getAspectRatioValue.at(m_renderOptions->aspectRatio);
    const int imageWidth = m_renderOptions->imageWidth;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = m_renderOptions->samplesPerPixel;
    const int maxDepth = m_renderOptions->maxDepth;

    // Renderer Output
    PPMStream ppmstream{imageWidth, imageHeight, randomName()};

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

    m_renderer.render(*finalscene, camera, ppmstream);   // main render

    auto end = std::chrono::steady_clock::now();

    std::cerr << "\nTime Elapsed in minutes: "
        << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
        << " minutes\n";
    std::cerr << "OR\n";
    std::cerr << "Time Elapsed in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " seconds\n";
}