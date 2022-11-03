#ifndef _CAMERA_H
#define _CAMERA_H

#include <stdexcept>

#include "../vec3.h"
#include "ray.h"

#include <string>

class Camera {
public:
    Camera(
        const double aspectRatio = 16.0 / 9.0,
        const Vec3 lookfrom = Point{0, 0, 0},
        const Vec3 lookat = Point{0, 0, -1},
        const Vec3 vup = Vec3{0, 1, 0},
        const double vfov = 90,
        const double aperture = 0,
        double focusDistance = 0
    ) {

        if (lookat == lookfrom) {
            throw std::invalid_argument("The Camera's \"lookfrom\" and \"lookat\" parameters may not be equal");
        }

        const double theta = degreesToRadians(vfov);
        const double h = tan(theta / 2.0);
        const double viewportHeight = 2.0 * h;
        const double viewportWidth = aspectRatio * viewportHeight;

        if (focusDistance == 0) {
            focusDistance = (lookfrom - lookat).length();
        }

        m_w = normalize(lookfrom - lookat);
        m_u = normalize(cross(vup, m_w));
        m_v = cross(m_w, m_u);

        m_origin = lookfrom;
        m_horizontal = focusDistance * viewportWidth * m_u;
        m_vertical = focusDistance * viewportHeight * m_v;
        m_lowerLeftCorner = m_origin - m_horizontal/2 - m_vertical/2 - focusDistance * m_w;

        m_lensRadius = aperture / 2.0;
    }

    Ray getRay(const double s, const double t) {
        #ifdef DEBUG
            if (s < 0 || s > 1 || t < 0 || t > 1) {
                throw std::out_of_range("Camera::getRay(" + std::to_string(s) + ", " + std::to_string(t) + ") parameters must be between 0 and 1 inclusive");
            } 
        #endif

        const Vec3 rd = m_lensRadius * Vec3::randomInUnitDisk();
        const Vec3 offset = m_u * rd.x() + m_v * rd.y(); 

        return Ray{
            m_origin + offset,
            m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset
        };
    }

private:
    Point m_origin;
    Point m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_v, m_u, m_w;
    double m_lensRadius;
};

#endif