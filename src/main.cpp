#include "Game.h"

int main(int argc, char *args[]) {
  Game::Instance().Init("Roguelike", 1280, 960);
  Game::Instance().Run();
  Game::Instance().Clean();
  return 0;
}
