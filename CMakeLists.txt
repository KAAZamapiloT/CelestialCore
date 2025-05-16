cmake_minimum_required(VERSION 3.15)
project(GameEngine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

# Use pkg-config for SDL2_image and SDL2_mixer
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

# Define source files
set(SOURCES
    main.cpp
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

# Define header files
set(HEADERS
    Objects/GameObject.h
    Objects/GameSprite.h
    subsystems/Audio.h
    subsystems/Render.h
    subsystems/AssetManager.h
    modules/scripts.h
    modules/Collision.h
    modules/Visual.h
    modules/Transformation.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL2::SDL2 
    glm::glm
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/subsystems
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_MIXER_CFLAGS_OTHER})

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Example usage executable
add_executable(AssetManagerExample examples/AssetManagerUsage.cpp subsystems/AssetManager.cpp)
target_link_libraries(AssetManagerExample PRIVATE
    SDL2::SDL2
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
target_include_directories(AssetManagerExample PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/subsystems
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)
target_compile_options(AssetManagerExample PRIVATE ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_MIXER_CFLAGS_OTHER}) 