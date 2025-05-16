/**
 * CelestialCore Editor - Entry Point
 * 
 * This is the main entry point for the CelestialCore game engine editor.
 */

#include "EditorMain.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Get editor instance
    EditorMain& editor = EditorMain::getInstance();
    
    // Initialize editor
    if (!editor.initialize("CelestialCore Editor", 1280, 720)) {
        std::cerr << "Failed to initialize editor!" << std::endl;
        return 1;
    }
    
    // Run the editor
    editor.run();
    
    // Successful exit
    return 0;
} 