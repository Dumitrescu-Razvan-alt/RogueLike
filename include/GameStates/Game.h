#pragma once
#include "Enemy.h"
#include "GameState.h"
#include "InputHandler.h"
#include "Map.h"
#include "MoveUI.h"
#include "Player.h"
#include "SDL_ttf.h"
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <memory>
#include <vector>

class Game {
public:
  static Game &Instance();

  void Init(const char *title, int width, int height);
  void Run();
  void Clean();
  void RenderMap();
  void RenderPlayer();
  void RenderEnemies();
  void RenderMoveUI();
  void ChangeState(std::unique_ptr<GameState> newState);
  void UpdateCamera();

  SDL_Renderer *GetRenderer() const { return renderer; }
  Player *GetPlayer() const { return player; }
  Map *GetMap() const { return map.get(); }
  InputHandler *GetInputHandler() { return inputHandler; }
  std::vector<Enemy> &GetEnemies() { return enemies; }
  bool IsRunning() const { return isRunning; }
  bool IsPlayerDead() const { return isDead; }
  void Quit() { isRunning = false; }
  void ResetGame();
  bool IsInitialized() const { return window != nullptr; }

  std::unique_ptr<Map> map;
  SDL_Texture *startTexture = nullptr;
  SDL_Texture *endTexture = nullptr;
  SDL_Texture *winTexture = nullptr;
  TTF_Font *font = nullptr;

  static const int TILE_SIZE = 32;
  static const int SCREEN_WIDTH = 640;
  static const int SCREEN_HEIGHT = 480;
  static const int MAP_WIDTH_TILES = 40;
  static const int MAP_HEIGHT_TILES = 30;
  int moves = 0;

private:
  Game() = default;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  bool isRunning = false;
  bool isDead = false;

  Player *player = nullptr;
  MoveUI *moveUI = nullptr;
  InputHandler *inputHandler = nullptr;

  SDL_Rect cameraOffset;

  std::vector<Enemy> enemies;

  std::unique_ptr<GameState> currentState;
};
