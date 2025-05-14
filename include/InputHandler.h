#pragma once
#include "Entity.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <memory>

class Command {
public:
  virtual ~Command() {}
  virtual void Execute(Entity &entity, std::unique_ptr<Map> &map) = 0;
};

class MoveUp : public Command {
public:
  void Execute(Entity &entity, std::unique_ptr<Map> &map) override {
    if (map->IsWalkable(entity.GetX(), entity.GetY() - 1))
      entity.Move(0, -1);
  }
};

class MoveDown : public Command {
public:
  void Execute(Entity &entity, std::unique_ptr<Map> &map) override {
    if (map->IsWalkable(entity.GetX(), entity.GetY() + 1))
      entity.Move(0, 1);
  }
};

class MoveLeft : public Command {
public:
  void Execute(Entity &entity, std::unique_ptr<Map> &map) override {
    if (map->IsWalkable(entity.GetX() - 1, entity.GetY()))
      entity.Move(-1, 0);
  }
};

class MoveRight : public Command {
public:
  void Execute(Entity &entity, std::unique_ptr<Map> &map) override {
    if (map->IsWalkable(entity.GetX() + 1, entity.GetY()))
      entity.Move(1, 0);
  }
};

class InputHandler {
public:
  std::unique_ptr<Command> HandleInput(const SDL_Event &e);
};
