#include "AssetManager.h"

// Singleton implementation
AssetManager& AssetManager::getInstance() {
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager() : mRenderer(nullptr) {}

AssetManager::~AssetManager() {
    clearAll();
}

bool AssetManager::initialize(SDL_Renderer* renderer) {
    if (!renderer) {
        std::cerr << "AssetManager: Invalid renderer provided" << std::endl;
        return false;
    }
    
    mRenderer = renderer;
    
    // Initialize SDL_image for texture loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    // Initialize SDL_mixer for audio loading
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool AssetManager::isInitialized() const {
    return mRenderer != nullptr;
}

// Texture management implementations
SDL_Texture* AssetManager::loadTexture(const std::string& id, const std::string& filePath) {
    if (!isInitialized()) {
        std::cerr << "AssetManager not initialized" << std::endl;
        return nullptr;
    }
    
    // Check if texture already exists
    if (mTextures.find(id) != mTextures.end()) {
        return mTextures[id]; // Return existing texture
    }
    
    // Load texture from file
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface); // Free the surface, we don't need it anymore
    
    if (!texture) {
        std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    // Store and return the loaded texture
    mTextures[id] = texture;
    return texture;
}

SDL_Texture* AssetManager::getTexture(const std::string& id) const {
    auto it = mTextures.find(id);
    if (it != mTextures.end()) {
        return it->second;
    }
    
    std::cerr << "Texture with id '" << id << "' not found" << std::endl;
    return nullptr;
}

bool AssetManager::unloadTexture(const std::string& id) {
    auto it = mTextures.find(id);
    if (it != mTextures.end()) {
        SDL_DestroyTexture(it->second);
        mTextures.erase(it);
        return true;
    }
    
    return false; // Texture not found
}

// Sound management implementations
Mix_Chunk* AssetManager::loadSound(const std::string& id, const std::string& filePath) {
    if (!isInitialized()) {
        std::cerr << "AssetManager not initialized" << std::endl;
        return nullptr;
    }
    
    // Check if sound already exists
    if (mSounds.find(id) != mSounds.end()) {
        return mSounds[id]; // Return existing sound
    }
    
    // Load sound from file
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        std::cerr << "Unable to load sound " << filePath << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    // Store and return the loaded sound
    mSounds[id] = sound;
    return sound;
}

Mix_Chunk* AssetManager::getSound(const std::string& id) const {
    auto it = mSounds.find(id);
    if (it != mSounds.end()) {
        return it->second;
    }
    
    std::cerr << "Sound with id '" << id << "' not found" << std::endl;
    return nullptr;
}

bool AssetManager::unloadSound(const std::string& id) {
    auto it = mSounds.find(id);
    if (it != mSounds.end()) {
        Mix_FreeChunk(it->second);
        mSounds.erase(it);
        return true;
    }
    
    return false; // Sound not found
}

// Music management implementations
Mix_Music* AssetManager::loadMusic(const std::string& id, const std::string& filePath) {
    if (!isInitialized()) {
        std::cerr << "AssetManager not initialized" << std::endl;
        return nullptr;
    }
    
    // Check if music already exists
    if (mMusic.find(id) != mMusic.end()) {
        return mMusic[id]; // Return existing music
    }
    
    // Load music from file
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Unable to load music " << filePath << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    // Store and return the loaded music
    mMusic[id] = music;
    return music;
}

Mix_Music* AssetManager::getMusic(const std::string& id) const {
    auto it = mMusic.find(id);
    if (it != mMusic.end()) {
        return it->second;
    }
    
    std::cerr << "Music with id '" << id << "' not found" << std::endl;
    return nullptr;
}

bool AssetManager::unloadMusic(const std::string& id) {
    auto it = mMusic.find(id);
    if (it != mMusic.end()) {
        Mix_FreeMusic(it->second);
        mMusic.erase(it);
        return true;
    }
    
    return false; // Music not found
}

// Clear all assets
void AssetManager::clearAll() {
    // Destroy all textures
    for (auto& pair : mTextures) {
        SDL_DestroyTexture(pair.second);
    }
    mTextures.clear();
    
    // Free all sounds
    for (auto& pair : mSounds) {
        Mix_FreeChunk(pair.second);
    }
    mSounds.clear();
    
    // Free all music
    for (auto& pair : mMusic) {
        Mix_FreeMusic(pair.second);
    }
    mMusic.clear();
} 