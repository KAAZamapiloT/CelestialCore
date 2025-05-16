#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../subsystems/AssetManager.h"

class GameSprite {
public:
    GameSprite();
    GameSprite(const std::string& textureId, const std::string& filePath);
    ~GameSprite();

    // Initialize the sprite with a texture from the asset manager
    bool initialize(const std::string& textureId, const std::string& filePath);

    // Load a different texture
    bool setTexture(const std::string& textureId);

    // Render the sprite at a given position
    void render(SDL_Renderer* renderer, int x, int y);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height);
    void render(SDL_Renderer* renderer, const SDL_Rect& destRect);

    // Set and get source rectangle (for sprite sheets)
    void setSourceRect(const SDL_Rect& rect);
    const SDL_Rect& getSourceRect() const;

    // Set sprite properties
    void setAlpha(Uint8 alpha);
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setFlip(SDL_RendererFlip flip);
    void setAngle(double angle);
    void setScale(float scaleX, float scaleY);

    // Get current dimensions
    int getWidth() const;
    int getHeight() const;
    
    // Check if sprite is valid
    bool isValid() const;

private:
    // Texture reference from asset manager
    std::string mTextureId;
    
    // Source rectangle for sprite sheets
    SDL_Rect mSrcRect;
    
    // Rendering properties
    double mAngle;
    SDL_Point mCenter;
    SDL_RendererFlip mFlip;
    
    // Scale factors
    float mScaleX;
    float mScaleY;
    
    // Original dimensions
    int mWidth;
    int mHeight;
}; 