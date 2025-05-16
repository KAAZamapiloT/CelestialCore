#include "GameSprite.h"

GameSprite::GameSprite() 
    : mTextureId(""), 
      mAngle(0.0), 
      mFlip(SDL_FLIP_NONE), 
      mScaleX(1.0f), 
      mScaleY(1.0f),
      mWidth(0),
      mHeight(0) {
    mSrcRect = {0, 0, 0, 0};
    mCenter = {0, 0};
}

GameSprite::GameSprite(const std::string& textureId, const std::string& filePath) 
    : mTextureId(""), 
      mAngle(0.0), 
      mFlip(SDL_FLIP_NONE), 
      mScaleX(1.0f), 
      mScaleY(1.0f),
      mWidth(0),
      mHeight(0) {
    mSrcRect = {0, 0, 0, 0};
    mCenter = {0, 0};
    initialize(textureId, filePath);
}

GameSprite::~GameSprite() {
    // No need to free textures here as they're managed by AssetManager
}

bool GameSprite::initialize(const std::string& textureId, const std::string& filePath) {
    // Use the asset manager to load the texture
    AssetManager& assetManager = AssetManager::getInstance();
    SDL_Texture* texture = assetManager.loadTexture(textureId, filePath);
    
    if (!texture) {
        return false;
    }
    
    // Get the dimensions of the texture
    SDL_QueryTexture(texture, nullptr, nullptr, &mWidth, &mHeight);
    
    // Set source rectangle to the full texture
    mSrcRect.x = 0;
    mSrcRect.y = 0;
    mSrcRect.w = mWidth;
    mSrcRect.h = mHeight;
    
    // Set center point
    mCenter.x = mWidth / 2;
    mCenter.y = mHeight / 2;
    
    // Store the texture id
    mTextureId = textureId;
    
    return true;
}

bool GameSprite::setTexture(const std::string& textureId) {
    AssetManager& assetManager = AssetManager::getInstance();
    SDL_Texture* texture = assetManager.getTexture(textureId);
    
    if (!texture) {
        return false;
    }
    
    // Get the dimensions of the texture
    SDL_QueryTexture(texture, nullptr, nullptr, &mWidth, &mHeight);
    
    // Update source rectangle to match new dimensions
    mSrcRect.w = mWidth;
    mSrcRect.h = mHeight;
    
    // Update center point
    mCenter.x = mWidth / 2;
    mCenter.y = mHeight / 2;
    
    // Store the texture id
    mTextureId = textureId;
    
    return true;
}

void GameSprite::render(SDL_Renderer* renderer, int x, int y) {
    if (!isValid()) return;
    
    // Calculate destination rectangle based on scale
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = static_cast<int>(mSrcRect.w * mScaleX);
    destRect.h = static_cast<int>(mSrcRect.h * mScaleY);
    
    render(renderer, destRect);
}

void GameSprite::render(SDL_Renderer* renderer, int x, int y, int width, int height) {
    if (!isValid()) return;
    
    SDL_Rect destRect = {x, y, width, height};
    render(renderer, destRect);
}

void GameSprite::render(SDL_Renderer* renderer, const SDL_Rect& destRect) {
    if (!isValid()) return;
    
    AssetManager& assetManager = AssetManager::getInstance();
    SDL_Texture* texture = assetManager.getTexture(mTextureId);
    
    if (texture) {
        SDL_RenderCopyEx(
            renderer,
            texture,
            &mSrcRect,
            &destRect,
            mAngle,
            &mCenter,
            mFlip
        );
    }
}

void GameSprite::setSourceRect(const SDL_Rect& rect) {
    mSrcRect = rect;
}

const SDL_Rect& GameSprite::getSourceRect() const {
    return mSrcRect;
}

void GameSprite::setAlpha(Uint8 alpha) {
    AssetManager& assetManager = AssetManager::getInstance();
    SDL_Texture* texture = assetManager.getTexture(mTextureId);
    
    if (texture) {
        SDL_SetTextureAlphaMod(texture, alpha);
    }
}

void GameSprite::setColor(Uint8 r, Uint8 g, Uint8 b) {
    AssetManager& assetManager = AssetManager::getInstance();
    SDL_Texture* texture = assetManager.getTexture(mTextureId);
    
    if (texture) {
        SDL_SetTextureColorMod(texture, r, g, b);
    }
}

void GameSprite::setFlip(SDL_RendererFlip flip) {
    mFlip = flip;
}

void GameSprite::setAngle(double angle) {
    mAngle = angle;
}

void GameSprite::setScale(float scaleX, float scaleY) {
    mScaleX = scaleX;
    mScaleY = scaleY;
}

int GameSprite::getWidth() const {
    return static_cast<int>(mWidth * mScaleX);
}

int GameSprite::getHeight() const {
    return static_cast<int>(mHeight * mScaleY);
}

bool GameSprite::isValid() const {
    AssetManager& assetManager = AssetManager::getInstance();
    return assetManager.getTexture(mTextureId) != nullptr;
} 