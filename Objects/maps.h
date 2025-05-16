#pragma once
#include<SDL2/SDL.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<string>
#include<vector>


class Background {
    public:
    Background(const std::string& textureId, const std::string& filePath);
    void render(SDL_Renderer* renderer);
    Background();
    ~Background();
    void setPosition(const glm::vec2& position);
    void setPosition(float x, float y);
    glm::vec2 getPosition() const;
    void setSize(const glm::vec2& size);
    void setSize(float width, float height);
    glm::vec2 getSize() const;
    void setTexture(const std::string& textureId);
};


class TileMap{
    public:
    Tilemap();
    ~Tilemap();
    
    bool Initialize(SDL_Renderer* renderer, const std::string& tileMapId, const std::string& filePath,int tileWidth, int tileHeight);
    void loadMap(const std::vector<std::vector<int>>& map);
    void render(SDL_Renderer* renderer);
    private:
    std::string mTilesetId;
    int mTileWidth;
    int mTileHeight;
    int mTilesetWidth;
    int mTilesetHeight;
    int mTilesPerRow;
    bool IsAnimated;
    std::vector<std::vector<int>> mMap;
    std::vector<std::vector<int>> mAnimatedTiles;
    std::vector<std::string>mProperties;
};