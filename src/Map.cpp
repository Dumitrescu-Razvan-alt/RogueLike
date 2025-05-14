#include "Map.h"
#include "Game.h"
#include "Tile.h"
#include "TileFactory.h"
#include <SDL_rect.h>
#include <SDL_render.h>
Map::Map(int width, int height, SDL_Texture* tileTexture) : width(width), height(height), tileTexture(tileTexture) {
    tiles.resize(height, std::vector<std::shared_ptr<Tile>>(width));
    GenerateTestMap();
}

void Map::GenerateTestMap(){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(x == 0 || y == 0 || x == width - 1 || y == height - 1 || (x % 5 == 0 && y % 5 == 0)){
                tiles[y][x] = TileFactory::CreateTile(TileType::Wall);
            }else {
                tiles[y][x] = TileFactory::CreateTile(TileType::Floor);
            }
        }
    }
}

void Map::Render(SDL_Renderer* rendere,SDL_Rect camerOffset){
    for (int y = 0; y < Game::SCREEN_HEIGHT/Game::TILE_SIZE; y++) {
        for (int x = 0; x < Game::SCREEN_WIDTH/Game::TILE_SIZE; x++) {
            tiles[y+camerOffset.y][x+camerOffset.x]->Render(rendere,tileTexture, x*32,y*32);
        }
    }
}

bool Map::IsWalkable(int x, int y) const{
    if(x<0 || y<0 || x>= width || y >= height) return false;
    return tiles[y][x] -> IsWalkable();
}
