#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GameObject.h"

int main(int argc, char* argv[]) {
    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    // Create window - note the different API compared to SDL2
    SDL_Window* window = SDL_CreateWindow("SDL3 Game Engine", 800, 600, 0);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    
    // Create renderer - note the different API compared to SDL2
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    // GLM example - create a transformation
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
    
    // Game loop
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Render code would go here
        
        // Present renderer
        SDL_RenderPresent(renderer);
        
        // Cap to 60 FPS
        SDL_Delay(16);
    }
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
