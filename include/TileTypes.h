#pragma once
#include "Tile.h"

class FloorTile : public Tile {
public:
    void Render(SDL_Renderer* renderer, SDL_Texture* texture, int screenX, int screenY) override;
    bool IsWalkable() const override { return true; }
};

class WallTile : public Tile {
public:
    void Render(SDL_Renderer* renderer, SDL_Texture* texture, int screenX, int screenY) override;
    bool IsWalkable() const override { return false; }
};
