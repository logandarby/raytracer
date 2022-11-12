#ifndef _VIEW_H
#define _VIEW_H

#include "common/pch.h"
#include "common/vec3.h"
#include "imgui.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

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
    // Quality
    int samplesPerPixel = 30;
    int maxDepth = 10;
    // Image sizing
    int imageWidth = 1280;
    int imageHeight = 720;
    bool landscape = true;
    AspectRatio aspectRatio = ASPECTRATIO_16_9;
    // Camera
    Vec3 lookFrom{0, 0, 2};
    Vec3 lookAt{0, 0, 0};
    float fov = 25;
    float focusDistance = 10;
    float aperture = 0.1;

    void applyAspectRatio() {
        updateHeight();
    }

    void updateHeight() {
        imageHeight = static_cast<int>(imageWidth / getAspectRatioValue.at(aspectRatio));
    }

    void updateWidth() {
        imageWidth = static_cast<int>(imageHeight * getAspectRatioValue.at(aspectRatio));
    }
};

// Custom implementation for inputting multiple doubles
namespace ImGui {
    bool InputDouble2(const char* label, double v[2], const char* format = "%.2f", ImGuiInputTextFlags flags = ImGuiInputTextFlags_None);
    bool InputDouble3(const char* label, double v[3], const char* format = "%.2f", ImGuiInputTextFlags flags = ImGuiInputTextFlags_None);
}

class View {
public:
    View() = default;
    ~View();
    bool Create(std::shared_ptr<RenderOptions> defaultRenderOptions);
    void Run();
private:
    void OptionsPanel();
    void RenderPanel();
    void AppMenuBar();
    void MainWindow();
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    std::shared_ptr<RenderOptions> m_renderOptions = nullptr;

    bool m_showOptionsPanel = true;
    bool m_showRenderPanel = true;
    bool m_showAppMenuBar = true;
    bool m_showDemoWindow = false;
};

#endif