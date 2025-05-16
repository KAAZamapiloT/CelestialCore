# CelestialCore Editor

The CelestialCore Editor is a graphical interface for the CelestialCore game engine, designed to provide intuitive tools for game development without writing code.

## Features (Planned)

- Scene editor with drag-and-drop functionality
- Asset management interface
- Component inspector
- Animation editor
- Tilemap editor
- Game preview/testing
- Project management

## Implementation

The editor is implemented using:
- Dear ImGui for UI elements
- SDL2 for windowing and rendering integration
- CelestialCore's own asset management and scene systems

## Usage

The editor can be launched using the provided script:

**Linux/macOS:**
```bash
# From the project root directory
./run_editor.sh
```

**Windows:**
```bash
# From the project root directory
run_editor.bat
```

Alternatively, you can build and run it manually:

```bash
# From the project root directory
mkdir -p build && cd build
cmake ..
make CelestialEditor
./bin/CelestialEditor
```

## Project Structure

- `EditorMain.h/.cpp` - Core editor functionality and window management
- `main.cpp` - Entry point for the editor application
- More panel classes will be added as features are implemented

## Development

This editor is currently under development. Key areas of focus:
- UI layout and workflow design
- Asset pipeline integration
- Scene serialization/deserialization
- Real-time editing capabilities

## Contributing

When contributing to the editor:
1. Follow the C++ code style of the main engine
2. Document all new UI components and their usage
3. Make sure all UI elements are responsive and scale properly
4. Test all interactions thoroughly before submitting PRs 