#pragma once

#include "Game.h"
#include "GameState.h"
class PlayingState : public GameState {
public:
  void Update(Game &game) override;
  void Render(Game &game) override;
};
