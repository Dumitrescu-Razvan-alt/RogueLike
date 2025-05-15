#pragma once
#include "Observer.h"
#include <SDL2/SDL.h>

class Player;

class MoveUI : public Observer {
public:
    MoveUI(Player* player);
    void OnNotify(Subject* subject) override;
    void Render(SDL_Renderer* renderer);

private:
    Player* player;
    int cachedMoves = 0;
    int currentTurnStep = 1;
};
