/**
 * CelestialCore_Export.h
 * 
 * Defines macros for exporting symbols from the CelestialCore shared library
 */

#pragma once

// Export macros for different platforms
#if defined(_WIN32) || defined(_WIN64)
    #ifdef CELESTIALCORE_EXPORTS
        #define CELESTIAL_API __declspec(dllexport)
    #else
        #define CELESTIAL_API __declspec(dllimport)
    #endif
#else
    #ifdef CELESTIALCORE_EXPORTS
        #define CELESTIAL_API __attribute__((visibility("default")))
    #else
        #define CELESTIAL_API
    #endif
#endif 