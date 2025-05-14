#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Entity.h"

class Command {
public:
    virtual ~Command() {}
    virtual void Execute(Entity& entity) = 0;
};

class MoveUp : public Command {
public:
    void Execute(Entity& entity) override { entity.Move(0, -1); }
};

class MoveDown : public Command {
public:
    void Execute(Entity& entity) override { entity.Move(0, 1); }
};

class MoveLeft : public Command {
public:
    void Execute(Entity& entity) override { entity.Move(-1, 0); }
};

class MoveRight : public Command {
public:
    void Execute(Entity& entity) override { entity.Move(1, 0); }
};

class InputHandler {
public:
    std::unique_ptr<Command> HandleInput(const SDL_Event& e);
};
