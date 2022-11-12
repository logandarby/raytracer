#include "common/pch.h"

#include "view.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <SDL.h>
#include "util/util.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

bool View::Create(std::shared_ptr<RenderOptions> defaultRenderOptions) {
    m_renderOptions = defaultRenderOptions;

    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to the latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    // Setup SDL_Renderer instance
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (m_renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        SDL_LogError(0, SDL_GetError());
        return false;
    }
    SDL_RendererInfo info;
    SDL_GetRendererInfo(m_renderer, &info);
    SDL_Log("Current window SDL_Renderer: %s", info.name);

    // Set up SDL Texture for rendering, and its associated renderer
    // SDL_Surface *surface = IMG_Load("images/checkerboard.png");
    // if (surface == NULL) {
    //     std::cerr << "ERROR: Could not load checkerboard image" << std::endl;
    // }
    // m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    // SDL_FreeSurface(surface);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
    if (!m_texture) {
        SDL_Log("Could not create blank texture!");
        SDL_LogError(0, SDL_GetError());
    }
    

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer_Init(m_renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    return true;
}

View::~View() {
    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void View::Run() {
    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        AppMenuBar();
        MainWindow();
        if(m_showDemoWindow)
            ImGui::ShowDemoWindow(&m_showDemoWindow);

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(m_renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(m_renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(m_renderer);
    }
}

void View::MainWindow() {
    static ImGuiWindowFlags mainWindowFlags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoSavedSettings;
    static ImGuiTableFlags mainTableFlags = 
        ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    auto optionsWidth = viewport->WorkSize.x/4;

    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::Begin("MainWindow", NULL, mainWindowFlags);

    ImGui::BeginTable("mainSplit", 2, mainTableFlags);
    ImGui::TableSetupColumn("Options", ImGuiTableColumnFlags_WidthFixed, optionsWidth);
    {   
        // Options Panel
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        OptionsPanel();
    }
    {
        // Render Panel
        ImGui::TableSetColumnIndex(1);
        RenderPanel();
    }

    ImGui::EndTable();
    ImGui::End();
}

void View::OptionsPanel() {
    static ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    static ImGuiTreeNodeFlags collpasingHeaderFlags =
        ImGuiTreeNodeFlags_DefaultOpen;

    static ImGuiSliderFlags sliderFlags = 
        ImGuiSliderFlags_AlwaysClamp;


    // ImGuiViewport* viewport = ImGui::GetMainViewport();

    if(!ImGui::BeginChild("Options", ImGui::GetContentRegionAvail(), false, window_flags)) {
        ImGui::EndChild();
        return;
    }
    ImGui::Text("Options");
    ImGui::Spacing();
    ImGui::Separator();
    if (ImGui::CollapsingHeader("Quality", collpasingHeaderFlags)) {
        ImGui::DragInt("Samples Per Pixel", &m_renderOptions->samplesPerPixel, 1.0f, 1, INT_INFINITY, "%d", sliderFlags);
        ImGui::DragInt("Max Depth", &m_renderOptions->maxDepth, 1.0f, 1, INT_INFINITY, "%d", sliderFlags);
        if (ImGui::InputInt("Image Width", &m_renderOptions->imageWidth)) {
            m_renderOptions->updateHeight();
        }
        if (ImGui::InputInt("Image Height", &m_renderOptions->imageHeight)) {
            m_renderOptions->updateWidth();
        }
        ImGui::Checkbox("Landspace", &m_renderOptions->landscape);

        // Aspect Ratio dropdown
        static AspectRatio& selectedKey = m_renderOptions->aspectRatio;
        const std::string selectedName = getAspectRatioName.at(selectedKey);
        if (ImGui::BeginCombo("Aspect Ratio", selectedName.c_str())) {
            for (auto &[key, val] : getAspectRatioName) {
                const bool isSelected = selectedKey == key;
                if (ImGui::Selectable(val.c_str(), isSelected)) {
                        selectedKey = key;
                        m_renderOptions->applyAspectRatio();
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    if (ImGui::CollapsingHeader("Camera", collpasingHeaderFlags)) {
        ImGui::InputDouble3("Look From Point", m_renderOptions->lookFrom.data(), "%.1f");
        ImGui::InputDouble3("Look At Point", m_renderOptions->lookAt.data(), "%.1f");
        ImGui::DragFloat("FOV", &m_renderOptions->fov, 0.0, 5.0, 90.0, "%.1f", sliderFlags);
        ImGui::DragFloat("Focus Distance", &m_renderOptions->focusDistance, 0.5, 0.0, FLT_INFINITY, "%.1f", sliderFlags);
        ImGui::DragFloat("Aperture", &m_renderOptions->aperture, 0.1, 0.0, FLT_INFINITY, "%.1f", sliderFlags);
    }
    
    ImGui::Spacing();

    if(ImGui::Button("Render")) {
        // Render the image
        std::cout << "pressed" << std::endl;
    }

    ImGui::EndChild();

}

void View::RenderPanel() {
    ImGui::Text("Render");
    ImGui::Spacing();
    ImGui::Separator();

    int w, h;
    SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
    // if (m_renderOptions->landscape) {
    //     w = m_renderOptions->imageWidth;
    //     h = m_renderOptions->imageHeight;
    // } else {
    //     h = m_renderOptions->imageWidth;
    //     w = m_renderOptions->imageHeight;
    // }

    int category = SDL_SetRenderTarget(m_renderer, m_texture);
    if (category < 0) {
        SDL_LogError(category, SDL_GetError());
    }

    SDL_Rect rect{0, 0, 100, 100};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &rect);

    ImGui::Image(m_texture, ImVec2{(float)w, (float)h});

    SDL_SetRenderTarget(m_renderer, NULL);

}

void View::AppMenuBar() {
    /*
    TOOLBAR:
        FILE:
            - export image >
                - ppm
                - jpg
                - png
        TOOLS:
            - tool menu in the demo window
    */
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Export Image", "CTRL+E")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Demo Window", NULL, &m_showDemoWindow)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

bool ImGui::InputDouble2(const char* label, double v[2], const char* format , ImGuiInputTextFlags flags) {
    return ImGui::InputScalarN(label, ImGuiDataType_Double, v, 2, NULL, NULL, format, flags);
}

bool ImGui::InputDouble3(const char* label, double v[3], const char* format , ImGuiInputTextFlags flags) {
    return ImGui::InputScalarN(label, ImGuiDataType_Double, v, 3, NULL, NULL, format, flags);
}