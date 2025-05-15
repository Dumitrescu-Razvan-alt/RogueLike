
#include "TileFactory.h"
#include "Tile.h"
#include "TileTypes.h"
#include <memory>
std::shared_ptr<Tile> TileFactory::CreateTile(TileType type) {
  switch (type) {
  case TileType::Floor:
    return std::make_shared<FloorTile>();
  case TileType::Wall:
    return std::make_shared<WallTile>();
  default:
    return nullptr;
  }
}
