#include "EditorMain.h"
#include <SDL2/SDL_image.h>
#include <iostream>

// Include ImGui
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

// Include engine components using the shared library
#include "../../subsystems/AssetManager.h"
#include "../../Objects/GameObject.h"
#include "../../Objects/GameSprite.h"

EditorMain::EditorMain()
    : mWindow(nullptr), mRenderer(nullptr), mImGuiContext(nullptr), mRunning(false), mWidth(0), mHeight(0) {
}

EditorMain::~EditorMain() {
    shutdown();
}

EditorMain& EditorMain::getInstance() {
    static EditorMain instance;
    return instance;
}

bool EditorMain::initialize(const std::string& title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Create window
    mWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!mWindow) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize ImGui
    if (!initializeImGui()) {
        std::cerr << "Failed to initialize ImGui!" << std::endl;
        return false;
    }

    // Initialize asset manager
    if (!AssetManager::getInstance().initialize(mRenderer)) {
        std::cerr << "Failed to initialize AssetManager!" << std::endl;
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(mRenderer, 64, 64, 64, 255);

    // Set running flag
    mRunning = true;
    mWidth = width;
    mHeight = height;

    return true;
}

bool EditorMain::initializeImGui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    mImGuiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if (!ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer)) {
        std::cerr << "Failed to initialize ImGui SDL2 implementation!" << std::endl;
        return false;
    }
    
    if (!ImGui_ImplSDLRenderer2_Init(mRenderer)) {
        std::cerr << "Failed to initialize ImGui SDL Renderer implementation!" << std::endl;
        return false;
    }

    return true;
}

void EditorMain::run() {
    Uint32 lastFrameTime = SDL_GetTicks();
    
    // Main loop
    while (mRunning) {
        // Calculate delta time
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
        
        // Process events
        processEvents();
        
        // Update
        update();
        
        // Render
        render();
    }
}

void EditorMain::shutdown() {
    // Shutdown ImGui
    shutdownImGui();
    
    // Clean up AssetManager
    AssetManager::getInstance().clearAll();
    
    // Clean up SDL resources
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void EditorMain::shutdownImGui() {
    if (mImGuiContext) {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext(mImGuiContext);
        mImGuiContext = nullptr;
    }
}

void EditorMain::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Pass events to ImGui
        ImGui_ImplSDL2_ProcessEvent(&event);
        
        // Process SDL events
        if (event.type == SDL_QUIT) {
            mRunning = false;
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                mWidth = event.window.data1;
                mHeight = event.window.data2;
            }
        }
    }
}

void EditorMain::update() {
    // Start the ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Create ImGui windows and widgets
    
    // Main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) {}
            if (ImGui::MenuItem("Open Project")) {}
            if (ImGui::MenuItem("Save Project")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                mRunning = false;
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Scene View")) {}
            if (ImGui::MenuItem("Game View")) {}
            if (ImGui::MenuItem("Inspector")) {}
            if (ImGui::MenuItem("Asset Browser")) {}
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
    
    // Scene hierarchy window
    ImGui::Begin("Scene Hierarchy");
    ImGui::Text("Game Objects:");
    if (ImGui::Button("Add Object")) {}
    ImGui::Separator();
    // List would go here
    ImGui::End();
    
    // Inspector window
    ImGui::Begin("Inspector");
    ImGui::Text("Properties:");
    // Properties would go here
    ImGui::End();
    
    // Asset browser window
    ImGui::Begin("Asset Browser");
    ImGui::Text("Assets:");
    // Assets would go here
    ImGui::End();
    
    // Demo window (for development only)
    //ImGui::ShowDemoWindow();
}

void EditorMain::render() {
    // Clear screen
    SDL_SetRenderDrawColor(mRenderer, 64, 64, 64, 255);
    SDL_RenderClear(mRenderer);
    
    // Render ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    
    // Update and render additional Platform Windows
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    
    // Present renderer
    SDL_RenderPresent(mRenderer);
} 