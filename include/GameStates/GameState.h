#pragma once

#include "Game.h"
class GameState {
public:
  virtual ~GameState();
  virtual void Render(Game &game) = 0;
  virtual void Update(Game &game) = 0;
};
