#ifndef _RENDER_OPTIONS_H
#define _RENDER_OPTIONS_H

// A struct to hold render options, and aspect ratio tools.

#include "common/pch.h"

#include "common/vec3.h"

enum AspectRatio {
    ASPECTRATIO_16_9 = 0,
    ASPECTRATIO_1_1,
    ASPECTRATIO_5_4,
    ASPECTRATIO_4_3,
    ASPECTRATIO_3_2
};

#define AD_PAIR(_AR, _DBL) std::pair<AspectRatio, double>{_AR, _DBL}
#define AS_PAIR(_AR, _STR) std::pair<AspectRatio, std::string>{_AR, _STR}

static const std::map<AspectRatio, double> getAspectRatioValue{
    AD_PAIR(ASPECTRATIO_16_9, 16.0 / 9.0),
    AD_PAIR(ASPECTRATIO_1_1, 1.0),
    AD_PAIR(ASPECTRATIO_5_4, 5.0 / 4.0),
    AD_PAIR(ASPECTRATIO_4_3, 4.0 / 3.0),
    AD_PAIR(ASPECTRATIO_3_2, 3.0 / 2.0),
};

static const std::map<AspectRatio, std::string> getAspectRatioName{
    AS_PAIR(ASPECTRATIO_16_9, "16 x 9"),
    AS_PAIR(ASPECTRATIO_1_1, "1 x 1"),
    AS_PAIR(ASPECTRATIO_5_4, "5 x 4"),
    AS_PAIR(ASPECTRATIO_4_3, "4 x 3"),
    AS_PAIR(ASPECTRATIO_3_2, "3 x 2"),
};

struct RenderOptions {
    static constexpr std::string NO_FILENAME = "";

    // Quality
    int samplesPerPixel = 10;
    int maxDepth = 10;
    // Image sizing
    int imageWidth = 300;
    int imageHeight = 200;
    bool landscape = true;
    AspectRatio aspectRatio = ASPECTRATIO_3_2;
    // Camera
    Vec3 lookFrom{13, 2, 3};
    Vec3 lookAt{0, 0, 0};
    float fov = 25;
    float focusDistance = 10;
    float aperture = 0.1;
    std::string filename = NO_FILENAME;

    void applyAspectRatio() {
        updateHeight();
    }

    void updateHeight() {
        imageHeight = static_cast<int>(imageWidth / getAspectRatioValue.at(aspectRatio));
    }

    void updateWidth() {
        imageWidth = static_cast<int>(imageHeight * getAspectRatioValue.at(aspectRatio));
    }

    void swapWidthAndHeight() {
        std::swap(imageHeight, imageWidth);
    }
};

#endif