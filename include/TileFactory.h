#pragma once
#include <memory>
#include "Tile.h"

enum class TileType {
    Floor,
    Wall
};

class TileFactory {
public:
    static std::shared_ptr<Tile> CreateTile(TileType type);
};
