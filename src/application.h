#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "common/pch.h"
#include "graphics/view.h"
#include "engine/renderer.h"
#include "common/renderOptions.h"
#include "event/event.h"

#include <thread>
#include <mutex>

class Application {
public:
    Application();
    void Run();
// private:
private:
    void Render();
    // thread safe way to stop rendining
    void stopRendering();
    void onEvent(Event &e);
    void onButtonPress(ButtonPressEvent &e);
    void onWindowClose(WindowCloseEvent &e);
    void onFieldModify(FieldModifyEvent &e);
private:
    std::shared_ptr<RenderOptions> m_renderOptions;
    View m_view;
    Renderer m_renderer;

    std::thread m_renderThread;
    std::mutex m_renderMutex;

    // # of items where the scene will use a Boundingn Volume Heirarchy
    const static int m_BVH_ITEM_CUTOFF = 15;
};


#endif