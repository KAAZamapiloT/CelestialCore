#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include<stdio.h>
#include "Objects/GameObject.h"
#include "subsystems/AssetManager.h"


GameObject* player;
player->setSprite("player", "assets/sprites/placeholder.png");
player->setSpeed(1000.0f);
int main(int argc, char* argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Init(SDL_INIT_EVENTS);
    
    // Create window - SDL2 API
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Game Engine", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        800, 
        600, 
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    
    // Create renderer - SDL2 API
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    // Initialize Asset Manager
    AssetManager& assetManager = AssetManager::getInstance();
    if (!assetManager.initialize(renderer)) {
        std::cerr << "AssetManager could not be initialized!" << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    // Load player texture
    assetManager.loadTexture("player", "assets/sprites/placeholder.png");
    
    // Create player game object with sprite
    player = new GameObject(1);
    player->setPosition(400.0f, 300.0f);
    player->setSize(64.0f, 64.0f);
    if (!player->setSprite("player")) {
        std::cerr << "Failed to set player sprite!" << std::endl;
    }
    
    // GLM example - create a transformation
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
    
    // Variables for the loop
    bool quit = false;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    
    // --- MAIN GAME LOOP ---
    while (!quit) {
        // --- CALCULATE TIME ---
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        // --- INPUT PHASE ---
        // Handle one-time events (quit, key presses)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            
            // Add other one-time events here (like starting a jump)
        }
        
        // --- UPDATE PHASE ---
        // Get current keyboard state for continuous movement
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        
        // Handle continuous keyboard input
        if (player) {
            // Simple way to directly move the player
            if (keyState[SDL_SCANCODE_W]) player->setPosition(player->getPosition().x, player->getPosition().y - 200 * deltaTime);
            if (keyState[SDL_SCANCODE_S]) player->setPosition(player->getPosition().x, player->getPosition().y + 200 * deltaTime);
            if (keyState[SDL_SCANCODE_A]) player->setPosition(player->getPosition().x - 200 * deltaTime, player->getPosition().y);
            if (keyState[SDL_SCANCODE_D]) player->setPosition(player->getPosition().x + 200 * deltaTime, player->getPosition().y);
            
            // Update any game logic
            player->update(deltaTime);
        }
        
        // --- RENDER PHASE ---
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Draw all game objects
        if (player) {
            player->render(renderer);
        }
        
        // Present the frame
        SDL_RenderPresent(renderer);
        
        // Optional: cap framerate
        SDL_Delay(16); // ~60 FPS
    }
    
    // Clean up
    delete player;
    // AssetManager will clean up assets in its destructor
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
