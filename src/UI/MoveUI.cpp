// src/ui/MoveUI.cpp
#include "MoveUI.h"
#include "Game.h"
#include "Player.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

MoveUI::MoveUI(Player* player_) : player(player_) {
    player->AddObserver(this);
}

void MoveUI::OnNotify(Subject* subject) {
        cachedMoves = player->GetMoveCount();
        currentTurnStep = player->GetCurrentTurnStep();
}

void MoveUI::Render(SDL_Renderer* renderer) {
    std::string text = "Moves: " + std::to_string(cachedMoves) +
                       " | Turn Step: " + std::to_string(currentTurnStep);

    // Background box
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200); // semi-transparent black
    SDL_Rect background = {10, 10, 300, 40};
    SDL_RenderFillRect(renderer, &background);

    // Render text
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(Game::Instance().font, text.c_str(), white);
    if (!textSurface) {
        // SDL_Log("Text surface failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        // SDL_Log("Text texture failed: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect destRect = {15, 15, textSurface->w, textSurface->h}; // adjust padding
    SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
