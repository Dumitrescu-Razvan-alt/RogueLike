// PlayingState.cpp
#include "PlayingState.h"
#include "EndState.h"
#include "Game.h"
#include "WinState.h"

void PlayingState::Update(Game &game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      game.Quit();
    }
  }

  auto command = game.GetInputHandler()->HandleInput();
  if (command) {
    if (command->Execute(*game.GetPlayer(), *game.GetMap())) {
      game.moves++;
      game.GetPlayer()->Update();
    }
    game.UpdateCamera();
    SDL_Delay(100);
  }
  if (game.GetPlayer()->GetX() == Game::MAP_WIDTH_TILES - 2 &&
      game.GetPlayer()->GetY() == Game::MAP_HEIGHT_TILES - 2)
    game.ChangeState(std::make_unique<WinState>());


  // Check for player-enemy collisions
  for (auto &enemy : game.GetEnemies()) {
    if (enemy.GetX() == game.GetPlayer()->GetX() &&
        enemy.GetY() == game.GetPlayer()->GetY()) {
      game.ChangeState(std::make_unique<EndState>());
      return;
    }
  }

  if (game.moves == 2) {
    for (auto &enemy : game.GetEnemies()) {
      enemy.Update();
    }
    game.moves = 0;
  }
}

void PlayingState::Render(Game &game) {
  SDL_SetRenderDrawColor(game.GetRenderer(), 0, 0, 0, 255);
  SDL_RenderClear(game.GetRenderer());

  game.RenderMap();
  game.RenderPlayer();
  game.RenderEnemies();
  game.RenderMoveUI();

  SDL_RenderPresent(game.GetRenderer());
}
