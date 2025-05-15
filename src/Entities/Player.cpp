#include "Player.h"
#include <iostream>

Player::Player(int x, int y) : Entity(x, y) {}

void Player::Update() {
    moveCount++;
    if(step < 2) step++;
    else step = 1;
    Notify();
}

void Player::Render(SDL_Renderer *renderer, SDL_Rect camerOffset) {
  SDL_Rect rect = {(x - camerOffset.x) * 32, (y - camerOffset.y) * 32, 32, 32};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow block
  SDL_RenderFillRect(renderer, &rect);
}
