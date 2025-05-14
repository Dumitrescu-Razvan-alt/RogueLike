#include "Player.h"

Player::Player(int x, int y) : Entity(x, y) {}

void Player::Update() {
    // No logic yet
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x * 32, y * 32, 32, 32 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow block
    SDL_RenderFillRect(renderer, &rect);
}
