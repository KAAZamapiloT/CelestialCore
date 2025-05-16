#!/bin/bash

# Color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Display a colorful banner
echo -e "${GREEN}"
echo "=================================================="
echo "          ImGui Setup for CelestialCore           "
echo "=================================================="
echo -e "${NC}"

# Create third_party directory if it doesn't exist
if [ ! -d "third_party" ]; then
    echo -e "${YELLOW}Creating third_party directory...${NC}"
    mkdir -p third_party
fi

# Clone ImGui if it doesn't exist
if [ ! -d "third_party/imgui" ]; then
    echo -e "${YELLOW}Cloning ImGui repository...${NC}"
    git clone https://github.com/ocornut/imgui.git third_party/imgui
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Failed to clone ImGui repository${NC}"
        exit 1
    fi
else
    echo -e "${YELLOW}ImGui already exists, updating...${NC}"
    cd third_party/imgui
    git pull
    cd ../..
fi

echo -e "${GREEN}ImGui setup complete!${NC}"