#include "TileTypes.h"
#include <SDL_rect.h>
#include <SDL_render.h>
SDL_Rect floorSrc = {32, 0, 32, 32};
SDL_Rect wallSrc = {0, 0, 32, 32};

void FloorTile::Render(SDL_Renderer *renderer, SDL_Texture *texture, int x,
                       int y) {
  SDL_Rect dest = {x, y, 32, 32};
  SDL_RenderCopy(renderer, texture, &floorSrc, &dest);
}
void WallTile::Render(SDL_Renderer *renderer, SDL_Texture *texture, int x,
                      int y) {
  SDL_Rect dest = {x, y, 32, 32};
  SDL_RenderCopy(renderer, texture, &wallSrc, &dest);
}
