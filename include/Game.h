#pragma once
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <memory>
#include "Map.h"
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
    std::unique_ptr<Map> map;

    static const int TILE_SIZE = 32;
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    const int MAP_WIDTH_TILES = 40;
    const int MAP_HEIGHT_TILES = 30;

private:
    Game() = default;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;

    Player* player = nullptr;
    InputHandler* inputHandler = nullptr;

    SDL_Rect cameraOffset;
};
