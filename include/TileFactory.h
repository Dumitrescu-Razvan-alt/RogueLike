#pragma once
#include "Tile.h"
#include <memory>

enum class TileType { Floor, Wall };

class TileFactory {
public:
  static std::shared_ptr<Tile> CreateTile(TileType type);
};
