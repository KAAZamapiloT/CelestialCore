@echo off
setlocal enabledelayedexpansion

:: Display a banner
echo ===================================================
echo          NexusEngine Game Launcher (SDL2)          
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

:: Build the project
echo Building the project...
cmake --build . --config Debug || (
    echo Build failed
    goto :error
)

:: Check if the game executable exists
if not exist "bin\Debug\GameEngine.exe" (
    echo Game executable not found. Build may have failed.
    goto :error
)

:: Run the game
echo Launching NexusEngine with SDL2...
cd bin\Debug || (
    echo Failed to navigate to bin directory
    goto :error
)
GameEngine.exe

:: Return to original directory when the game exits
cd ..\..\..
echo Game session ended.
goto :eof

:error
cd ..
echo An error occurred during the build or launch process.
pause
exit /b 1 