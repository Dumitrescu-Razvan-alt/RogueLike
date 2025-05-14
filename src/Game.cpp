#include "Game.h"

Game& Game::Instance() {
    static Game instance;
    return instance;
}

void Game::Init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;

    player = new Player(5, 5);
    inputHandler = new InputHandler();
}

void Game::Run() {
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        auto command = inputHandler->HandleInput(event);
        if (command) command->Execute(*player);
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player->Render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}

void Game::Clean() {
    delete player;
    delete inputHandler;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
