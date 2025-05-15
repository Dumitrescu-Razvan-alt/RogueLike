#pragma once
#include "Entity.h"
#include "Subject.h"

class Player : public Entity, public Subject {
public:
  Player(int x, int y);
  void Update() override;
  void Render(SDL_Renderer *renderer, SDL_Rect camerOffset) override;
  int GetMoveCount() const {return moveCount;}
  int GetCurrentTurnStep() const {return step;}
private:
    int moveCount = 0;
    int step = 0;
};
