#pragma once

#include "../CelestialCore_Export.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

class CELESTIAL_API AssetManager {
public:
    // Singleton pattern
    static AssetManager& getInstance();
    
    // Initialize the asset manager
    bool initialize(SDL_Renderer* renderer);
    
    // Texture management
    SDL_Texture* loadTexture(const std::string& id, const std::string& filePath);
    SDL_Texture* getTexture(const std::string& id) const;
    bool unloadTexture(const std::string& id);
    
    // Sound management
    Mix_Chunk* loadSound(const std::string& id, const std::string& filePath);
    Mix_Chunk* getSound(const std::string& id) const;
    bool unloadSound(const std::string& id);
    
    // Music management
    Mix_Music* loadMusic(const std::string& id, const std::string& filePath);
    Mix_Music* getMusic(const std::string& id) const;
    bool unloadMusic(const std::string& id);
    
    // Font management (if needed in the future)
    
    // Clear all assets
    void clearAll();
    
private:
    AssetManager();
    ~AssetManager();
    
    // Delete copy constructor and assignment operator
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    
    // Renderer reference
    SDL_Renderer* mRenderer;
    
    // Asset containers
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::unordered_map<std::string, Mix_Chunk*> mSounds;
    std::unordered_map<std::string, Mix_Music*> mMusic;
    
    // Helper methods
    bool isInitialized() const;
}; 