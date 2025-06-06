#pragma once

#include "Entity.h"
#include "Map.h"
#include "MovementStrategy.h"
#include "Player.h"
#include "SDL_render.h"
#include <memory>
class Enemy : public Entity {
public:
  Enemy(int x, int y, std::unique_ptr<MovementStrategy> strategy, Map &map, Player& player, SDL_Texture* texture);
  void Update() override;
  void Render(SDL_Renderer *renderer, SDL_Rect cameraOffset) override;

private:
  std::unique_ptr<MovementStrategy> strategy;
  Map &map ;
  Player &player;
  SDL_Texture *texture;
};
