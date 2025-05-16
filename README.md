# CelestialCore Game Engine

CelestialCore is a 2D game engine built with SDL2 and GLM, designed to provide a flexible and easy-to-use framework for game development.

## Project Structure

The project is organized as follows:

- **Core Engine (Shared Library)**
  - `Objects/` - Game object classes and components
  - `subsystems/` - Core engine subsystems (rendering, audio, etc.)
  - `modules/` - Functional modules (collision, transformations, etc.)
  - `assets/` - Asset directory for sprites, sounds, music

- **Editor**
  - `ui/editor/` - Separate editor application using Dear ImGui

## Requirements

- CMake 3.15+
- C++17 compatible compiler
- SDL2
- SDL2_image
- SDL2_mixer
- GLM
- Git (for downloading ImGui)

## Building the Project

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/CelestialCore.git
cd CelestialCore
```

### 2. Setup ImGui for the editor

```bash
# Linux/macOS
./setup_imgui.sh

# Windows
setup_imgui.bat
```

### 3. Build with CMake

```bash
mkdir build
cd build
cmake ..
make
```

This will build:
- `libCelestialCore.so` (or .dll on Windows) - The engine shared library
- `CelestialRuntime` - The engine runtime executable
- `CelestialEditor` - The editor application

## Running the Editor

```bash
# Linux/macOS
./run_editor.sh

# Windows
run_editor.bat
```

## Using the Engine in Your Game

### CMake Integration

To use CelestialCore in your own game project, add the following to your CMakeLists.txt:

```cmake
# Find CelestialCore package
find_package(CelestialCore REQUIRED)

# Create your game executable
add_executable(YourGame main.cpp)

# Link with CelestialCore
target_link_libraries(YourGame PRIVATE CelestialCore)
```

### Code Example

```cpp
#include <CelestialCore/Objects/GameObject.h>
#include <CelestialCore/subsystems/AssetManager.h>

int main(int argc, char* argv[]) {
    // Initialize SDL and create window/renderer
    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_UNDEFINED, 
                                         SDL_WINDOWPOS_UNDEFINED, 800, 600, 
                                         SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               SDL_RENDERER_ACCELERATED);
    
    // Initialize asset manager
    AssetManager::getInstance().initialize(renderer);
    
    // Create game objects
    GameObject player(1);
    player.setSprite("player", "assets/sprites/player.png");
    player.setPosition(400, 300);
    
    // Game loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    
    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            player.handleInput(event);
        }
        
        // Update game objects
        player.update(deltaTime);
        
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        player.render(renderer);
        
        SDL_RenderPresent(renderer);
    }
    
    // Cleanup
    AssetManager::getInstance().clearAll();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
```

## License

This project is licensed under the MIT License - see the LICENSE file for details. 