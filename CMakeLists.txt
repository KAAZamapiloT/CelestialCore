cmake_minimum_required(VERSION 3.15)
project(GameEngine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)

# Define source files
set(SOURCES
    main.cpp
    GameObject.cpp
    subsystems/Audio.cpp
    subsystems/Render.cpp
    modules/scripts.cpp
    modules/Collision.cpp
    modules/Visual.cpp
    modules/Transformation.cpp
)

# Define header files
set(HEADERS
    GameObject.h
    subsystems/Audio.h
    subsystems/Render.h
    modules/scripts.h
    modules/Collision.h
    modules/Visual.h
    modules/Transformation.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glm::glm)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/subsystems
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 