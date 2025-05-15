#pragma once
#include "Entity.h"

class Player : public Entity {
public:
  Player(int x, int y);
  void Update() override;
  void Render(SDL_Renderer *renderer, SDL_Rect camerOffset) override;
};
