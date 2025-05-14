#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include "InputHandler.h"

class Game {
public:
    static Game& Instance();

    void Init(const char* title, int width, int height);
    void Run();
    void Clean();

    SDL_Renderer* GetRenderer() const { return renderer; }
    bool IsRunning() const { return isRunning; }

private:
    Game() = default;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;

    Player* player = nullptr;
    InputHandler* inputHandler = nullptr;
};
