# CelestialCore Editor CMakeLists.txt
project(CelestialEditor VERSION 0.1.0 LANGUAGES CXX)

# Define ImGui source files
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

# Define editor source files
set(EDITOR_SOURCES
    main.cpp
    EditorMain.cpp
    ${IMGUI_SOURCES}
)

# Define editor header files
set(EDITOR_HEADERS
    EditorMain.h
)

# Create editor executable
add_executable(${PROJECT_NAME} ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# Link with the engine library
target_link_libraries(${PROJECT_NAME} PRIVATE 
    CelestialCore
    SDL2::SDL2
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Include directories for editor
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/subsystems
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_SOURCE_DIR}/Objects
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

# Add compile options for editor
target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_MIXER_CFLAGS_OTHER}) 