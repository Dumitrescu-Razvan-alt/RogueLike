#pragma once

#include "InputHandler.h"
class MovementStrategy {
public:
  virtual ~MovementStrategy() = default;
  virtual std::unique_ptr<Command> CalculateCommand(int &dx, int &dy) = 0;
};

class NormalMovement : public MovementStrategy {
public:
  std::unique_ptr<Command> CalculateCommand(int &dx, int &dy);
};

class DiagonalMovement : public MovementStrategy {
public:
  std::unique_ptr<Command> CalculateCommand(int &dx, int &dy);
};
