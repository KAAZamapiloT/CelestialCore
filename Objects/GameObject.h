#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"Transformation.h"

class Object{
    public:
    Object(int ID);
    Object();


private:
int id;
void Move2D(){
switch(event){
    case SDL_KEY_s:
     Transform2D::location += glm::vec2(0,1);
     break;
    case SDL_KEY_w:
        Transform2D::location -= glm::vec2(0,1);
        break;
    case SDL_KEY_a:
        Transform2D::location -= glm::vec2(1,0);
        break;
    case SDL_KEY_d:
        Transform2D::location += glm::vec2(1,0);
        break;
}
}

};