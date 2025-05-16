#include "GameObject.h"

GameObject::GameObject() : id(0), width(0.0f), height(0.0f) {
}

GameObject::GameObject(int ID) : id(ID), width(0.0f), height(0.0f) {
}

void GameObject::handleInput(SDL_Event& event) {
    //Move2D(event);
    Update(deltaTime);
    //UpdateAnimation(deltaTime);
}

void GameObject::update(float deltaTime) {
    // Update logic here
    this->deltaTime = deltaTime;
    updateMovement(deltaTime);
}

void GameObject::render(SDL_Renderer* renderer) {
    // Render the sprite at the GameObject's position
    if (sprite.isValid()) {
        sprite.render(renderer, 
                      static_cast<int>(location.x), 
                      static_cast<int>(location.y),
                      static_cast<int>(width),
                      static_cast<int>(height));
    }else{
        printf("\nSprite is not valid\n");
    }
}

void GameObject::audio() {
    // Audio logic here
}

bool GameObject::setSprite(const std::string& textureId, const std::string& filePath) {
    bool success = sprite.initialize(textureId, filePath);
    
    // If width and height are not set, use the sprite dimensions
    if (success && width == 0.0f && height == 0.0f) {
        width = static_cast<float>(sprite.getWidth());
        height = static_cast<float>(sprite.getHeight());
    }
    
    return success;
}

bool GameObject::setSprite(const std::string& textureId) {
    bool success = sprite.setTexture(textureId);
    
    // If width and height are not set, use the sprite dimensions
    if (success && width == 0.0f && height == 0.0f) {
        width = static_cast<float>(sprite.getWidth());
        height = static_cast<float>(sprite.getHeight());
    }
    
    return success;
}

GameSprite* GameObject::getSprite() {
    return &sprite;
}

void GameObject::setPosition(float x, float y) {
    location.x = x;
    location.y = y;
}

void GameObject::setPosition(const glm::vec2& pos) {
    location = pos;
}

const glm::vec2& GameObject::getPosition() const {
    return location;
}

void GameObject::setSize(float w, float h) {
    width = w;
    height = h;
}

float GameObject::getWidth() const {
    return width;
}

float GameObject::getHeight() const {
    return height;
}

int GameObject::getId() const {
    return id;
}
