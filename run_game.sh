#!/bin/bash

# Color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Display a colorful banner
echo -e "${GREEN}"
echo "=================================================="
echo "          Celestial Engine Game Launcher (SDL2)        "
echo "=================================================="
echo -e "${NC}"

# Check if build directory exists
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Build directory not found. Creating it now...${NC}"
    mkdir -p build
fi

# Navigate to build directory
cd build || { echo -e "${RED}Failed to navigate to build directory${NC}"; exit 1; }

# Check if CMake has been run
if [ ! -f "Makefile" ]; then
    echo -e "${YELLOW}Running CMake...${NC}"
    cmake .. || { echo -e "${RED}CMake configuration failed${NC}"; exit 1; }
fi

# Build the project
echo -e "${YELLOW}Building the project...${NC}"
make -j$(nproc) || { echo -e "${RED}Build failed${NC}"; exit 1; }

# Check if the game executable exists
if [ ! -f "GameEngine" ]; then
    echo -e "${RED}Game executable not found. Build may have failed.${NC}"
    exit 1
fi

# Run the game
echo -e "${GREEN}Launching NexusEngine with SDL2...${NC}"
./GameEngine

# Return to original directory when the game exits
cd ..
echo -e "${GREEN}Game session ended.${NC}" 