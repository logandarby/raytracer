#ifndef _RENDERER_H
#define _RENDERER_H

#include "material.h"

class Hittable;
class Camera;
class HitRecord;
class Ray;

class Renderer {
public:
    Renderer(
        const int imageWidth,
        const int imageHeight,
        const int samplesPerPixel = 20,     // how many rays are shot per pixel
        const int maxDepth = 10             // maximum times a single ray may be reflected
    );

    void render(const Hittable &scene, const Camera &camera);
    void stop();
    bool isRunning();

private:
    Color traceRay(const Ray &r, const unsigned int depth);
    Color hitColor(const HitRecord &rec);
    Color missColor(const Ray &r);

    const Hittable *m_activeScene = nullptr;
    const Camera *m_activeCamera = nullptr;

    int m_imageWidth;
    int m_imageHeight;
    int m_samplesPerPixel;
    int m_maxDepth;

    // For threading
    volatile bool m_running = false;
};

#endif