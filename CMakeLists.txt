cmake_minimum_required(VERSION 3.15)
project(CelestialCore VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find dependencies
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

# Use pkg-config for SDL2_image and SDL2_mixer
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

# Define source files for the engine library
set(ENGINE_SOURCES
    Objects/GameObject.cpp
    Objects/GameSprite.cpp
    subsystems/Audio.cpp
    subsystems/Render.cpp
    subsystems/AssetManager.cpp
    modules/scripts.cpp
    modules/Collision.cpp
    modules/Visual.cpp
    modules/Transformation.cpp
)

# Define header files for the engine library
set(ENGINE_HEADERS
    Objects/GameObject.h
    Objects/GameSprite.h
    subsystems/Audio.h
    subsystems/Render.h
    subsystems/AssetManager.h
    modules/scripts.h
    modules/Collision.h
    modules/Visual.h
    modules/Transformation.h
    CelestialCore_Export.h
)

# Create shared library for the engine
add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Set version properties for the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Link libraries for the engine
target_link_libraries(${PROJECT_NAME} PUBLIC 
    SDL2::SDL2 
    glm::glm
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Include directories for the engine
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/subsystems
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

# Add compile options for the engine
target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_MIXER_CFLAGS_OTHER})

# Define macros for exporting symbols when building shared library
target_compile_definitions(${PROJECT_NAME} PRIVATE CELESTIALCORE_EXPORTS)

# Create main engine executable (game runtime)
add_executable(CelestialRuntime main.cpp)
target_link_libraries(CelestialRuntime PRIVATE ${PROJECT_NAME})

# Editor - Separate project
add_subdirectory(ui/editor)

# Example usage executables
add_executable(AssetManagerExample examples/AssetManagerUsage.cpp)
target_link_libraries(AssetManagerExample PRIVATE ${PROJECT_NAME})

add_executable(SharedLibraryUsage examples/SharedLibraryUsage.cpp)
target_link_libraries(SharedLibraryUsage PRIVATE ${PROJECT_NAME}) 