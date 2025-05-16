//#include<ASSImp>
//mesh optimizer
// sprite handeler

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Transformation.h"

class Mesh {
public:
    Mesh();
    explicit Mesh(const std::string& filePath);
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;
};

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& filePath);
    
    SDL_Texture* texture;
    glm::vec2 dimensions;
    glm::vec2 pivot;
};

class Voxel {
public:
    Voxel();
    explicit Voxel(const glm::ivec3& dimensions);
    
    glm::ivec3 dimensions;
    std::vector<unsigned int> data;
};