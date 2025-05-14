#include "Game.h"

int main(int argc, char* args[]) {
    Game::Instance().Init("Roguelike", 640, 480);
    Game::Instance().Run();
    Game::Instance().Clean();
    return 0;
}
