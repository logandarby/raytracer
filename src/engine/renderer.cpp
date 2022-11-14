#include "common/pch.h"

#include "renderer.h"
#include "ray.h"
#include "hittable.h"
#include "camera.h"
#include "util/util.h"

Renderer::Renderer(
    const int imageWidth,
    const int imageHeight,
    const int samplesPerPixel,    // how many rays are shot per pixel
    const int maxDepth               // maximum times a single ray may be reflected
) :
    m_imageWidth{imageWidth},
    m_imageHeight{imageHeight},
    m_samplesPerPixel{samplesPerPixel}, 
    m_maxDepth{maxDepth}
{}

void Renderer::stop() {
    m_running = false;
    std::cerr << "Renderer Stopped" << std::endl;
}

bool Renderer::isRunning() {
    return m_running;
}


void Renderer::render(const Hittable &scene, const Camera &camera) {
    m_running = true;
    m_activeCamera = &camera;
    m_activeScene = &scene;

    for (int j = m_imageHeight - 1; j >= 0 && m_running; --j) {
	    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_imageWidth && m_running; ++i) {
            // antialiasing
            Color pixel{0, 0, 0};
            for (int s = 0; s < m_samplesPerPixel; s++) {
                double u = double(i + fastRandomDouble()) / (m_imageWidth - 1);
                double v = double(j + fastRandomDouble()) / (m_imageHeight - 1);
                Ray r = m_activeCamera->getRay(u, v);
                pixel += traceRay(r, m_maxDepth);
            }
            writeColor(std::cout, pixel, m_samplesPerPixel);
        }
    }
}

Color Renderer::traceRay(const Ray& r, const unsigned int depth) {

    if (depth <= 0) {
        return Color{0, 0, 0};
    }

    HitRecord rec{};
    if (!m_activeScene->hit(r, 0.001, DBL_INFINITY, rec)) {
        return missColor(r);
    }
    Ray scattered;
    Color attenuation;
    Color emitted = rec.materialPtr->emmitted();
    if (!rec.materialPtr->scatter(r, rec, attenuation, scattered)) {
        return emitted;
    }
    return emitted + attenuation * traceRay(scattered, depth - 1);
}



Color Renderer::hitColor(const HitRecord &rec) {
    (void)rec;
    return V_BLACK;
}

Color Renderer::missColor(const Ray &r) {
    // background gradient
    Vec3 unit_direction = normalize(r.direction());
    const double t = 0.5*(unit_direction.y() + 1.0);
    const Color skyColor = (1.0-t)*Color{1.0, 1.0, 1.0} + t*Color{0.5, 0.7, 1.0};

    return V_BLACK + 0.05 * skyColor;
}
