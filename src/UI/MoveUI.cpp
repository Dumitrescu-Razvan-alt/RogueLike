// src/ui/MoveUI.cpp
#include "MoveUI.h"
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
        std::cout<<cachedMoves << " " <<  currentTurnStep << "\n";
}

void MoveUI::Render(SDL_Renderer* renderer) {
    // Example: draw rectangles or use SDL_ttf if available
    std::string text = "Moves: " + std::to_string(cachedMoves) + " | Turn Step: " + std::to_string(currentTurnStep);
    //std::cout<<text << "\n";
    // Render text using SDL_ttf or simply draw colored bars for demo
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect background = {10, 10, 250, 30};
    SDL_RenderFillRect(renderer, &background);

    // If using TTF, render text here
    // SDL_RenderCopy(renderer, fontTexture, ...);
}
