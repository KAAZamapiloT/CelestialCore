#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

// Forward declarations for ImGui
struct ImGuiContext;

class EditorMain {
public:
    // Singleton pattern
    static EditorMain& getInstance();

    // Initialize the editor
    bool initialize(const std::string& title, int width, int height);

    // Run the editor main loop
    void run();

    // Shutdown the editor
    void shutdown();

private:
    EditorMain();
    ~EditorMain();

    // Delete copy constructor and assignment operator
    EditorMain(const EditorMain&) = delete;
    EditorMain& operator=(const EditorMain&) = delete;

    // Handle events
    void processEvents();

    // Update editor state
    void update();

    // Render the editor
    void render();

    // Initialize ImGui
    bool initializeImGui();

    // Shutdown ImGui
    void shutdownImGui();

    // SDL resources
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    // ImGui context
    ImGuiContext* mImGuiContext;

    // Editor state
    bool mRunning;
    int mWidth;
    int mHeight;
}; 