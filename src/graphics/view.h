#ifndef _VIEW_H
#define _VIEW_H

#include "common/pch.h"

class SDL_Window;
class SDL_Renderer;

struct RenderOptions {
    // Quality
    int samplesPerPixel = 30;
    int maxDepth = 10;
    double aspectRatio = 3.0 / 2.0;
    double imageWidth = 1000;
    // Camera
    float lookFrom[3] = {0, 0, 2};
    float lookAt[3] = {0, 0, 0};
    float fov = 25;
    float focusDistance = 10;
    float aperture = 0.1;
};

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
    std::shared_ptr<RenderOptions> m_renderOptions = nullptr;

    bool m_showOptionsPanel = true;
    bool m_showRenderPanel = true;
    bool m_showAppMenuBar = true;
    bool m_showDemoWindow = false;
};

#endif