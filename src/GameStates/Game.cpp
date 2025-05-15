#include "Game.h"
#include "Map.h"
#include "MoveUI.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "StartState.h"
#include <SDL_image.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <iostream>
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
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  if (TTF_Init() == -1) {
       std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
   }
  font = TTF_OpenFont("../assets/font2.ttf",24);
  SDL_Surface *startImage = IMG_Load("../assets/start.png");
  SDL_Surface *endImage = IMG_Load("../assets/end.png");
  SDL_Surface *winImage = IMG_Load("../assets/win.png");

  startTexture = SDL_CreateTextureFromSurface(renderer, startImage);
  endTexture = SDL_CreateTextureFromSurface(renderer, endImage);
  winTexture = SDL_CreateTextureFromSurface(renderer, winImage);

  SDL_Texture *tileTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  SDL_FreeSurface(startImage);
  SDL_FreeSurface(endImage);
  SDL_FreeSurface(winImage);

  map =
      std::make_unique<Map>(width / TILE_SIZE, height / TILE_SIZE, tileTexture);
  map->GenerateTestMap();

  enemies.emplace_back(5, 6, std::make_unique<NormalMovement>(), *map, *player);
  enemies.emplace_back(14, 10, std::make_unique<DiagonalMovement>(), *map,
                       *player);

  isRunning = true;

  player = new Player(10, 7);
  moveUI = new MoveUI(player);
  player->AddObserver(moveUI);
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

void Game::RenderMap() { map->Render(renderer, cameraOffset); }
void Game::RenderPlayer() { player->Render(renderer, cameraOffset); }
void Game::RenderEnemies() {
  for (auto &enemy : enemies)
    enemy.Render(renderer, cameraOffset);
}
void Game::RenderMoveUI(){moveUI->Render(renderer);}

//   void Game::Run() {
//   int moves = 0;
//   while (isRunning) {
//     SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//       if (event.type == SDL_QUIT)
//         isRunning = false;
//     }

//     auto command = inputHandler->HandleInput();
//     if (command) {
//       if (command->Execute(*player, *map))
//         moves++;
//       UpdateCamera();
//       SDL_Delay(100);
//     }
//     for (auto &enemy : enemies) {
//       if (enemy.GetX() == player->GetX() && enemy.GetY() == player->GetY())
//         isRunning = false;
//     }
//     if (moves == 2) {
//       for (auto &enemy : enemies) {
//         enemy.Update();
//       }

//       moves = 0;
//     }

//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);

//     RenderMap();
//     RenderPlayer();
//     RenderEnemies();

//     SDL_RenderPresent(renderer);
//   }
// }

void Game::Run() {
  // Start with the start screen state
  currentState = std::make_unique<StartState>();

  while (isRunning) {
    currentState->Update(*this);
    currentState->Render(*this);
  }
}
void Game::ChangeState(std::unique_ptr<GameState> newState) {
  currentState = std::move(newState);
}

void Game::ResetGame() {
  enemies.clear();
  delete player;
  delete inputHandler;

  map->GenerateTestMap();

  enemies.emplace_back(5, 6, std::make_unique<NormalMovement>(), *map, *player);
  enemies.emplace_back(14, 10, std::make_unique<DiagonalMovement>(), *map,
                       *player);

  isRunning = true;

  player = new Player(10, 7);
  moveUI = new MoveUI(player);
  player->AddObserver(moveUI);
  inputHandler = new InputHandler();

  cameraOffset = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Game::Clean() {
  delete player;
  delete inputHandler;
  IMG_Quit();
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyTexture(startTexture);
  SDL_DestroyTexture(endTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
