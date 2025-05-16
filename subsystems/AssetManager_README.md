# Asset Manager

The Asset Manager is a singleton class that handles loading, storing, and unloading various types of game assets such as textures, sounds, and music.

## Features

- Singleton design pattern for easy access throughout the game
- Manages textures using SDL2_image
- Manages sound effects and music using SDL2_mixer
- Automatic cleanup of assets when the program exits
- Prevents duplicate loading of assets with the same ID

## Dependencies

- SDL2
- SDL2_image
- SDL2_mixer

## Usage

### Initialization

```cpp
// Get the singleton instance
AssetManager& assetManager = AssetManager::getInstance();

// Initialize with renderer
if (!assetManager.initialize(renderer)) {
    // Handle initialization error
}
```

### Loading Assets

```cpp
// Load a texture
SDL_Texture* playerTexture = assetManager.loadTexture("player", "assets/sprites/player.png");

// Load a sound effect
Mix_Chunk* jumpSound = assetManager.loadSound("jump", "assets/sounds/jump.wav");

// Load music
Mix_Music* backgroundMusic = assetManager.loadMusic("bgm", "assets/music/background.mp3");
```

### Getting Assets

```cpp
// Get previously loaded assets by ID
SDL_Texture* playerTexture = assetManager.getTexture("player");
Mix_Chunk* jumpSound = assetManager.getSound("jump");
Mix_Music* backgroundMusic = assetManager.getMusic("bgm");
```

### Unloading Assets

```cpp
// Unload specific assets
assetManager.unloadTexture("player");
assetManager.unloadSound("jump");
assetManager.unloadMusic("bgm");

// Unload all assets
assetManager.clearAll();
```

## Example

See `examples/AssetManagerUsage.cpp` for a complete working example of how to use the AssetManager. 