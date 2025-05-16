#include <SDL2/SDL.h>
#include "../Objects/GameObject.h"
#include "../subsystems/AssetManager.h"
#include <iostream>

/**
 * This example demonstrates how to use the CelestialCore engine as a shared library.
 * 
 * To compile this example manually (after building the engine):
 * 
 * g++ -o SharedLibraryUsage SharedLibraryUsage.cpp -L../build/lib -lCelestialCore -Wl,-rpath,../build/lib `pkg-config --cflags --libs sdl2 SDL2_image SDL2_mixer`
 */

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "CelestialCore Shared Library Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize the AssetManager (from the shared library)
    AssetManager& assetManager = AssetManager::getInstance();
    if (!assetManager.initialize(renderer)) {
        std::cerr << "Failed to initialize AssetManager!" << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load a texture using the AssetManager
    SDL_Texture* texture = assetManager.loadTexture("placeholder", "assets/sprites/placeholder.png");
    if (!texture) {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    // Create a GameObject (from the shared library)
    GameObject gameObject(1);
    gameObject.setPosition(400, 300);
    gameObject.setSize(100, 100);
    gameObject.setSprite("placeholder", "assets/sprites/placeholder.png");

    // Main loop
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            // Pass events to the GameObject
            gameObject.handleInput(event);
        }

        // Update game objects
        gameObject.update(deltaTime);

        // Render
        SDL_SetRenderDrawColor(renderer, 32, 32, 64, 255);
        SDL_RenderClear(renderer);
        
        // Render the GameObject
        gameObject.render(renderer);
        
        // Display information text
        SDL_Rect infoRect = {10, 10, 400, 30};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(renderer, &infoRect);
        
        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    assetManager.clearAll();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 