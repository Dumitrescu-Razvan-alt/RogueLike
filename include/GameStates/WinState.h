#pragma once

#include "Game.h"
#include "GameState.h"
class WinState : public GameState {
public:
  void Update(Game &game) override;
  void Render(Game &game) override;
};
