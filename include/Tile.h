#pragma once
#include <SDL2/SDL.h>

class Tile {
public:
    virtual ~Tile() = default;
    virtual void Render(SDL_Renderer* renderer, SDL_Texture* texture, int screenX, int screenY) = 0;
    virtual bool IsWalkable() const = 0;
};
