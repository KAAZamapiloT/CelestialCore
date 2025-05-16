#include <SDL2/SDL.h>
#include <iostream>
#include "../subsystems/AssetManager.h"

// Example of how to use the AssetManager in your game

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    // Get the dimensions of the texture
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Set rendering destination
    SDL_Rect dstRect = { x, y, width, height };

    // Render the texture
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize!" << std::endl;
        return -1;
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("AssetManager Example", SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize the AssetManager
    AssetManager& assetManager = AssetManager::getInstance();
    if (!assetManager.initialize(renderer)) {
        std::cerr << "Failed to initialize AssetManager" << std::endl;
        return -1;
    }

    // Load assets
    SDL_Texture* placeholderTexture = assetManager.loadTexture("placeholder", "assets/sprites/placeholder.png");
    
    // Check if assets loaded successfully
    if (!placeholderTexture) {
        std::cerr << "Failed to load placeholder texture" << std::endl;
        return -1;
    } else {
        std::cout << "Successfully loaded placeholder texture!" << std::endl;
    }

    // Game loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render our placeholder texture
        if (placeholderTexture) {
            renderTexture(renderer, placeholderTexture, 400, 300);
        }

        // Present the rendered image
        SDL_RenderPresent(renderer);

        // Cap to 60 FPS
        SDL_Delay(16);
    }

    // AssetManager will clean up all assets when the program exits
    
    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 