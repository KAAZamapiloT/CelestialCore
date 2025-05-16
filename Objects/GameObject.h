#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../CelestialCore_Export.h"
#include "../subsystems/HandleInput.h"
#include "../subsystems/Render.h"
#include "../subsystems/Audio.h"
#include "GameSprite.h"
#include"stdio.h"

class CELESTIAL_API GameObject {
public:
    GameObject(int ID);
    GameObject();
    
    // Basic game object operations
    void handleInput(SDL_Event& event);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void audio();
    
    // Sprite management
    bool setSprite(const std::string& textureId, const std::string& filePath);
    bool setSprite(const std::string& textureId);
    GameSprite* getSprite();
    
    // Position and movement
    void setPosition(float x, float y);
    void setPosition(const glm::vec2& pos);
    const glm::vec2& getPosition() const;
    
    // Size
    void setSize(float width, float height);
    float getWidth() const;
    float getHeight() const;
    
    // ID
    int getId() const;

private:
    int id;
    float speed = 1000.0f; // Pixels per second
    float deltaTime = 0.0f;
    
    void Move2D(SDL_Event& event) {
        updateMovement(deltaTime);
        // Handle one-time key press events here if needed
    }
    
    // Add this new method for continuous movement
    void updateMovement(float dt) {
        deltaTime = dt;
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        
        if (keyState[SDL_SCANCODE_W]) {
            location.y -= speed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_S]) {
            location.y += speed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_A]) {
            location.x -= speed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_D]) {
            location.x += speed * deltaTime;
        }
        printf("\nLocation: %f, %f\n", location.x, location.y);
    }
    void setSpeed(float speed) {
        this->speed = speed;
    }
    float getSpeed() const {
        return speed;
    }
    // Position
    glm::vec2 location = glm::vec2(0.0f);
    
    // Size
    float width = 0.0f;
    float height = 0.0f;
    // Sprite component
    GameSprite sprite;
};