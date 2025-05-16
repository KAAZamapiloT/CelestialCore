@echo off
setlocal enabledelayedexpansion

:: Display a banner
echo ===================================================
echo          CelestialCore Editor Launcher            
echo ===================================================
echo.

:: Check if build directory exists
if not exist "build" (
    echo Build directory not found. Creating it now...
    mkdir build
)

:: Navigate to build directory
cd build || (
    echo Failed to navigate to build directory
    goto :error
)

:: Check if CMake has been run
if not exist "CMakeFiles" (
    echo Running CMake...
    cmake .. -G "Visual Studio 17 2022" || (
        echo CMake configuration failed
        goto :error
    )
)

:: Build the engine library first
echo Building the CelestialCore engine library...
cmake --build . --config Debug --target CelestialCore || (
    echo Engine build failed
    goto :error
)

:: Build the editor
echo Building the CelestialCore Editor...
cmake --build . --config Debug --target CelestialEditor || (
    echo Editor build failed
    goto :error
)

:: Check if the editor executable exists
if not exist "bin\Debug\CelestialEditor.exe" (
    echo Editor executable not found. Build may have failed.
    goto :error
)

:: Set PATH to include the library directory
set PATH=%cd%\lib\Debug;%PATH%

:: Run the editor
echo Launching CelestialCore Editor...
cd bin\Debug || (
    echo Failed to navigate to bin directory
    goto :error
)
CelestialEditor.exe %*

:: Return to original directory when the editor exits
cd ..\..\..
echo Editor session ended.
goto :eof

:error
cd ..
echo An error occurred during the build or launch process.
pause
exit /b 1 