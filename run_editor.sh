#!/bin/bash

# Color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Display a colorful banner
echo -e "${GREEN}"
echo "=================================================="
echo "          CelestialCore Editor Launcher           "
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

# Build the engine library first
echo -e "${YELLOW}Building the CelestialCore engine library...${NC}"
make CelestialCore -j$(nproc) || { echo -e "${RED}Engine build failed${NC}"; exit 1; }

# Build the editor
echo -e "${YELLOW}Building the CelestialCore Editor...${NC}"
make CelestialEditor -j$(nproc) || { echo -e "${RED}Editor build failed${NC}"; exit 1; }

# Check if the editor executable exists
if [ ! -f "bin/CelestialEditor" ]; then
    echo -e "${RED}Editor executable not found. Build may have failed.${NC}"
    exit 1
fi

# Set LD_LIBRARY_PATH to find the engine library
export LD_LIBRARY_PATH="${PWD}/lib:${LD_LIBRARY_PATH}"

# Run the editor
echo -e "${GREEN}Launching CelestialCore Editor...${NC}"
./bin/CelestialEditor "$@"

# Return to original directory when the editor exits
cd ..
echo -e "${GREEN}Editor session ended.${NC}" 