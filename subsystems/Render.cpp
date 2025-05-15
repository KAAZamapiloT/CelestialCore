#include "Render.h"
#include <iostream>

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
    
    // Create window - SDL3 API
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // Create renderer - SDL3 API
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
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
    SDL_FRect destRect;
    destRect.x = transform.location.x;
    destRect.y = transform.location.y;
    destRect.w = sprite.dimensions.x * transform.scale.x;
    destRect.h = sprite.dimensions.y * transform.scale.y;
    
    // Create center point for rotation
    SDL_FPoint center;
    center.x = sprite.pivot.x * destRect.w;
    center.y = sprite.pivot.y * destRect.h;
    
    // Render texture with rotation
    SDL_RenderTextureRotated(renderer, sprite.texture, NULL, &destRect, 
                           transform.rotation * 180.0f / M_PI, &center, SDL_FLIP_NONE);
}

void Renderer::renderMesh(const Mesh& mesh, const Transform3D& transform) {
    // This would typically require a 3D rendering system
    // For SDL3, this is simplified and would normally use OpenGL/Vulkan/DirectX
    // Just a placeholder for now
}
