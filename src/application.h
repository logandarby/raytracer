#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "common/pch.h"
#include "graphics/view.h"
#include "engine/renderer.h"
#include "common/renderOptions.h"

class Application {
public:
    Application() : 
        m_renderOptions{std::make_shared<RenderOptions>()},
        m_view{},
        m_renderer{m_renderOptions->imageWidth, m_renderOptions->imageHeight}
    {}
    void Run();
// private:
    void Render();
private:
    std::shared_ptr<RenderOptions> m_renderOptions;
    View m_view;
    Renderer m_renderer;

    bool m_USE_BVH = false;
};


#endif