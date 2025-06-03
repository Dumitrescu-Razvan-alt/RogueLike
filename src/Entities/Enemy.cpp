// Enemy.cpp
#include "Enemy.h"
#include "Player.h"
#include <SDL_render.h>

Enemy::Enemy(int x, int y, std::unique_ptr<MovementStrategy> strategy,Map &map, Player &player,SDL_Texture* texture)
    : Entity(x, y), strategy(std::move(strategy)), map(map), player(player), texture(texture) {}

    void Enemy::Update() {
        int x = this->GetX();
        int y = this->GetY();
        auto command = strategy->CalculateCommand(x, y);
        if (command) {
            command->Execute(*this, map);
        }
    }

void Enemy::Render(SDL_Renderer* renderer, SDL_Rect cameraOffset) {
    SDL_Rect rect = {(x - cameraOffset.x) * 32, (y - cameraOffset.y) * 32, 32, 32};

    SDL_Rect src = {0, 32, 32, 32};
    SDL_RenderCopy(renderer, texture, &src, &rect);
}
