# NexusEngine - Game Engine with SDL3 and GLM

NexusEngine is a lightweight C++ game engine built with SDL3 and GLM math library, designed for 2D and 3D game development. This project aims to provide a simple but powerful foundation for creating cross-platform games.

## Features

- SDL3-based rendering system
- GLM-powered math and transformation system
- 2D and 3D object support
- Component-based architecture
- Modern C++17 implementation
- Asset Manager for handling textures, sound effects, and music
- Game Object system with Sprite composition
- Input handling system

## GameObject System

The engine uses a GameObject-based architecture. GameObjects are the main entities in your game and can have various components:

### GameObject

The GameObject class is the base class for all game entities. It has the following features:

- Position and size management
- Input handling
- Update and render functionality
- Sprite composition for visual representation

### Sprite Component

GameObjects use Sprite composition for visual representation:

- Each GameObject contains a Sprite object
- Sprites are connected to textures via the AssetManager
- Sprites can be animated, scaled, rotated, and colored
- Multiple rendering methods for flexibility

## Asset Manager

The Asset Manager is responsible for loading and managing game assets:

- Textures (using SDL3)
- Sound effects (using SDL3)
- Music (using SDL3)

## Dependencies

- [SDL3](https://github.com/libsdl-org/SDL) - Simple DirectMedia Layer 3
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics
- C++17 compatible compiler
- CMake 3.15 or higher

## Build Instructions

### Linux/macOS

```bash
# Clone the repository
git clone https://github.com/yourusername/NexusEngine.git
cd NexusEngine

# Create a build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
make

# Run the application
./bin/GameEngine
```

### Windows

```bash
# Clone the repository
git clone https://github.com/yourusername/NexusEngine.git
cd NexusEngine

# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project (using Visual Studio or MinGW)
cmake --build .

# Run the application
.\bin\Debug\GameEngine.exe
```

## Project Structure

- `/modules` - Core engine modules
  - `Transformation` - Handles 2D/3D transformations
  - `Visual` - Manages sprites, meshes, and voxels
  - `Collision` - Collision detection system
  - `Scripts` - Scripting system

- `/subsystems` - Engine subsystems
  - `Render` - Rendering subsystem
  - `Audio` - Audio subsystem

- `/Objects` - Game object definitions

## Usage Example

```cpp
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "subsystems/Render.h"
#include "modules/Transformation.h"
#include "modules/Visual.h"

int main() {
    // Initialize the renderer
    Renderer renderer;
    renderer.initialize("My Game", 800, 600);
    
    // Create a sprite
    Sprite sprite("assets/player.png");
    
    // Create a transform
    Transform2D transform;
    transform.location = glm::vec2(400, 300);
    transform.scale = glm::vec2(1.0f, 1.0f);
    
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
        
        // Update logic
        transform.rotation += 0.01f;
        
        // Render
        renderer.beginFrame();
        renderer.renderSprite(sprite, transform);
        renderer.endFrame();
    }
    
    renderer.shutdown();
    return 0;
}
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -m 'Add some feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Open a Pull Request 