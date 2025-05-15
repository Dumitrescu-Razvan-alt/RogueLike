// GameOverState.cpp
#include "WinState.h"
#include "Game.h"
#include "StartState.h"
#include <SDL.h>

void WinState::Update(Game& game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.Quit();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            // Return to start screen
            game.ResetGame();
            game.ChangeState(std::make_unique<StartState>());
        }
    }
}

void WinState::Render(Game& game) {
    SDL_SetRenderDrawColor(game.GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(game.GetRenderer());

    SDL_RenderCopy(game.GetRenderer(), game.winTexture, nullptr, nullptr);

    SDL_RenderPresent(game.GetRenderer());
}
