// StartScreenState.cpp
#include "StartState.h"
#include "Game.h"
#include "PlayingState.h"
#include "SDL_render.h"
#include <SDL.h>

void StartState::Update(Game& game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.Quit();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            // if (!game.IsInitialized()) {
            //     game.Init("Roguelike", 1280, 960);
            // }
            game.ChangeState(std::make_unique<PlayingState>());
        }
    }
}

void StartState::Render(Game& game) {
    SDL_SetRenderDrawColor(game.GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(game.GetRenderer());

    SDL_RenderCopy(game.GetRenderer(), game.startTexture, nullptr, nullptr);

    SDL_RenderPresent(game.GetRenderer());
}
