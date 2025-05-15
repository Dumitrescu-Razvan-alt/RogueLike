#pragma once
#include "Tile.h"
#include <SDL_render.h>
#include <memory>
#include <vector>

class Map {
public:
  Map(int width, int height, SDL_Texture *tileTexture);
  void GenerateTestMap();
  void Render(SDL_Renderer *renderer, SDL_Rect camerOffset);

  bool IsWalkable(int x, int y) const;

private:
  int width, height;
  std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
  SDL_Texture *tileTexture = nullptr;
};
