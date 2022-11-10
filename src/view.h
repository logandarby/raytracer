#ifndef _VIEW_H
#define _VIEW_H

class SDL_Window;
class SDL_Renderer;

class View {
public:
    View() = default;
    bool Create();
    void Destroy();
    void Run();
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif