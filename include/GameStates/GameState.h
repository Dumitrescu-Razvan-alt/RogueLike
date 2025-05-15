#pragma once

class Game;

class GameState {
public:
  virtual ~GameState() = default;
  virtual void Render(Game &game) = 0;
  virtual void Update(Game &game) = 0;
};
