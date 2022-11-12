#ifndef _VIEW_H
#define _VIEW_H

#include "common/pch.h"
#include "common/renderOptions.h"
#include "imgui.h"
#include "textureStream.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

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
    // updates dimensions of texture based off RenderOptions
    bool updateTextureDimensions();
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::shared_ptr<RenderOptions> m_renderOptions = nullptr;

    TextureStream m_tStream;

    bool m_showOptionsPanel = true;
    bool m_showRenderPanel = true;
    bool m_showAppMenuBar = true;
    bool m_showDemoWindow = false;
};

#endif