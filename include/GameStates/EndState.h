#pragma once

#include "Game.h"
#include "GameState.h"
class EndState : public GameState {
public:
  void Update(Game &game) override;
  void Render(Game &game) override;
};
