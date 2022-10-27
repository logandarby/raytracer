#ifndef _CAMERA_H
#define _CAMERA_H

#include <stdexcept>

#include "../vec3.h"
#include "ray.h"

#include <string>

class Camera {
public:
    Camera() {
        const auto aspectRatio = 16.0 / 9.0;
        double viewportHeight = 2.0;
        double viewportWidth = aspectRatio * viewportHeight;
        double focalHeight = 1.0;

        m_origin = Point{0, 0, 0};
        m_horizontal = Vec3{viewportWidth, 0, 0};
        m_vertical = Vec3{0, viewportHeight, 0};
        m_lowerLeftCorner = m_origin - m_horizontal/2 - m_vertical/2 - Vec3{0, 0, focalHeight};
    }

    Ray getRay(const double u, const double v) {
        // if (u < 0 || u > 1 || v < 0 || v > 1) {
        //     throw std::out_of_range("Camera::getRay(" + std::to_string(u) + ", " + std::to_string(v) + ") parameters must be between 0 and 1 inclusive");
        // } 
        return Ray{m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin};
    }

private:
    Point m_origin;
    Point m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};

#endif