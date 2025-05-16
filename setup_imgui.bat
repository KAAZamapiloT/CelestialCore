@echo off
setlocal enabledelayedexpansion

:: Display a banner
echo ===================================================
echo          ImGui Setup for CelestialCore            
echo ===================================================
echo.

:: Check if Git is installed
where git >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Git is not installed or not in PATH. Please install Git and try again.
    goto :error
)

:: Create third_party directory if it doesn't exist
if not exist "third_party" (
    echo Creating third_party directory...
    mkdir third_party
)

:: Clone ImGui if it doesn't exist
if not exist "third_party\imgui" (
    echo Cloning ImGui repository...
    git clone https://github.com/ocornut/imgui.git third_party\imgui
    
    if %ERRORLEVEL% NEQ 0 (
        echo Failed to clone ImGui repository
        goto :error
    )
) else (
    echo ImGui already exists, updating...
    cd third_party\imgui
    git pull
    cd ..\..
)

echo ImGui setup complete!
goto :eof

:error
echo An error occurred during the ImGui setup process.
pause
exit /b 1