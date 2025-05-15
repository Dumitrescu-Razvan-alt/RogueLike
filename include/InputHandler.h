#pragma once
#include "Entity.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL_scancode.h>
#include <array>
#include <memory>

class Command {
public:
  virtual ~Command() {}
  virtual bool Execute(Entity &entity, Map &map) = 0;
};

class MoveUp : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX(), entity.GetY() - 1)) {
      entity.Move(0, -1);
      return true;
    }
    return false;
  }
};

class MoveDown : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX(), entity.GetY() + 1)) {
      entity.Move(0, 1);
      return true;
    }
    return false;
  }
};

class MoveLeft : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() - 1, entity.GetY())) {
      entity.Move(-1, 0);
      return true;
    }
    return false;
  }
};

class MoveRight : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() + 1, entity.GetY())) {
      entity.Move(1, 0);
      return true;
    }
    return false;
  }
};

class MoveUpLeft : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() - 1, entity.GetY() - 1)) {
      entity.Move(-1, -1);
      return true;
    }
    return false;
  }
};

class MoveUpRight : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() + 1, entity.GetY() - 1)) {
      entity.Move(1, -1);
      return true;
    }
    return false;
  }
};

class MoveDownLeft : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() - 1, entity.GetY() + 1)) {
      entity.Move(-1, 1);
      return true;
    }
    return false;
  }
};

class MoveDownRight : public Command {
public:
  bool Execute(Entity &entity, Map &map) override {
    if (map.IsWalkable(entity.GetX() + 1, entity.GetY() + 1)) {
      entity.Move(1, 1);
      return true;
    }
    return false;
  }
};

class InputHandler {
public:
  InputHandler() { std::fill(prevKeystate.begin(), prevKeystate.end(), 0); }
  std::unique_ptr<Command> HandleInput();

private:
  std::array<Uint8, SDL_NUM_SCANCODES> prevKeystate;
};
