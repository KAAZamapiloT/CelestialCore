#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <string>
#include "../modules/Visual.h"
#include "../modules/Transformation.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize(const std::string& title, int width, int height);
    void shutdown();
    
    void beginFrame();
    void endFrame();
    
    void renderSprite(const Sprite& sprite, const Transform2D& transform);
    void renderMesh(const Mesh& mesh, const Transform3D& transform);
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int windowWidth;
    int windowHeight;
};