#include "Game.h"
#include "Map.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <memory>

Game &Game::Instance() {
  static Game instance;
  return instance;
}

void Game::Init(const char *title, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface *surface = SDL_LoadBMP("../assets/tiles.bmp");

  SDL_Texture *tileTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  map =
      std::make_unique<Map>(width / TILE_SIZE, height / TILE_SIZE, tileTexture);
  map->GenerateTestMap();

  enemies.emplace_back(5, 6, std::make_unique<NormalMovement>(), *map, *player);
  enemies.emplace_back(14, 10, std::make_unique<DiagonalMovement>(), *map,
                       *player);

  isRunning = true;

  player = new Player(10, 7);
  inputHandler = new InputHandler();

  cameraOffset = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Game::UpdateCamera() {

  if (player->GetX() - SCREEN_WIDTH / TILE_SIZE / 2 < 0)
    cameraOffset.x = 0;
  else if (player->GetX() + SCREEN_WIDTH / TILE_SIZE / 2 > MAP_WIDTH_TILES) {
  } else
    cameraOffset.x = player->GetX() - SCREEN_WIDTH / TILE_SIZE / 2;
  if (player->GetY() - SCREEN_HEIGHT / TILE_SIZE / 2 < 0)
    cameraOffset.y = 0;
  else if (player->GetY() + SCREEN_HEIGHT / TILE_SIZE / 2 + 1 >
           MAP_HEIGHT_TILES) {
  } else
    cameraOffset.y = player->GetY() - SCREEN_HEIGHT / TILE_SIZE / 2;
}

void Game::Run() {
  int moves = 0;
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        isRunning = false;
    }

    auto command = inputHandler->HandleInput();
    if (command) {
      if (command->Execute(*player, *map))
        moves++;
      UpdateCamera();
      SDL_Delay(100);
    }
    for (auto &enemy : enemies) {
        if (enemy.GetX() == player->GetX() && enemy.GetY() == player->GetY())
          isRunning = false;
    }
    if (moves == 2) {
      for (auto &enemy : enemies) {
        enemy.Update();
      }

        moves = 0;
      }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      map->Render(renderer, cameraOffset);
      player->Render(renderer, cameraOffset);
      for (auto &enemy : enemies)
        enemy.Render(renderer, cameraOffset);

      SDL_RenderPresent(renderer);
    }
  }

  void Game::Clean() {
    delete player;
    delete inputHandler;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
