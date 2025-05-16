#include "Render.h"
#include <iostream>
#include <cmath>

Renderer::Renderer() : window(nullptr), renderer(nullptr), windowWidth(0), windowHeight(0) {
}

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::initialize(const std::string& title, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create window - SDL2 API
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // Create renderer - SDL2 API
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    return true;
}

void Renderer::shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    SDL_Quit();
}

void Renderer::beginFrame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::endFrame() {
    SDL_RenderPresent(renderer);
}

void Renderer::renderSprite(const Sprite& sprite, const Transform2D& transform) {
    if (!sprite.texture) return;
    
    // Create destination rectangle
    SDL_Rect destRect;
    destRect.x = static_cast<int>(transform.location.x);
    destRect.y = static_cast<int>(transform.location.y);
    destRect.w = static_cast<int>(sprite.dimensions.x * transform.scale.x);
    destRect.h = static_cast<int>(sprite.dimensions.y * transform.scale.y);
    
    // Create center point for rotation
    SDL_Point center;
    center.x = static_cast<int>(sprite.pivot.x * destRect.w);
    center.y = static_cast<int>(sprite.pivot.y * destRect.h);
    
    // Render texture with rotation in SDL2
    SDL_RenderCopyEx(
        renderer, 
        sprite.texture, 
        NULL, 
        &destRect, 
        transform.rotation * 180.0f / M_PI, 
        &center, 
        SDL_FLIP_NONE
    );
}

void Renderer::renderMesh(const Mesh& mesh, const Transform3D& transform) {
    // This would typically require a 3D rendering system
    // For SDL2, this is simplified and would normally use OpenGL/Vulkan/DirectX
    // Just a placeholder for now
}
