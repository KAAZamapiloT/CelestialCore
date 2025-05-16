#include <SDL2/SDL.h>

class InputComponent{
    public:
    InputComponent();
    ~InputComponent();
    void handleInput(const SDL_Event& event);
    void update(float deltaTime);
};
