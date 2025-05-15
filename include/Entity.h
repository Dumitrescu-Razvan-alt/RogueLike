#pragma once
#include <SDL2/SDL.h>

class Entity {
public:
  Entity(int x, int y) : x(x), y(y) {}
  virtual void Update() = 0;
  virtual void Render(SDL_Renderer *renderer, SDL_Rect camerOffset) = 0;

  void Move(int dx, int dy) {
    x += dx;
    y += dy;
  }
  int GetX() const { return x; }
  int GetY() const { return y; }
  void SetPosition(int x, int y) const {
    x = x;
    y = y;
  }

protected:
  int x, y;
};
