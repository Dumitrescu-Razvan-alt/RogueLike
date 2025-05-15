// Enemy.cpp
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include <SDL_render.h>

Enemy::Enemy(int x, int y, std::unique_ptr<MovementStrategy> strategy,Map &map, Player &player)
    : Entity(x, y), strategy(std::move(strategy)), map(map), player(player) {}

    // Enemy.cpp
    void Enemy::Update() {
        bool moved = false;
        while(!moved){
            int* filler1 = 0, filler2 = 0;
            auto command = strategy->CalculateCommand(filler2,filler2);
            if (command) {
                moved = command->Execute(*this, map);
            }

        }
    }

void Enemy::Render(SDL_Renderer* renderer, SDL_Rect cameraOffset) {
    // if(x < player.GetX() - cameraOffset.x || x > player.GetX() + cameraOffset.x || y < player.GetY() - cameraOffset.y || y > player.GetY() + cameraOffset.y)
    //     return;

    SDL_Rect rect = {(x - cameraOffset.x) * 32, (y - cameraOffset.y) * 32, 32, 32};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black color
    SDL_RenderFillRect(renderer, &rect);
}
