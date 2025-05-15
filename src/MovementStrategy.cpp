#include "MovementStrategy.h"
#include "InputHandler.h"
#include <memory>
std::unique_ptr<Command> NormalMovement::CalculateCommand(int &dx, int &dy) {
  int direction = rand() % 4;
  switch (direction) {
  case 0:
    return std::make_unique<MoveUp>();
  case 1:
    return std::make_unique<MoveDown>();
  case 2:
    return std::make_unique<MoveLeft>();
  case 3:
    return std::make_unique<MoveRight>();
  }
  return nullptr;
}

std::unique_ptr<Command> DiagonalMovement::CalculateCommand(int &dx, int &dy) {
  int direction = rand() % 4;
  switch (direction) {
  case 0:
    return std::make_unique<MoveUpLeft>();
  case 1:
    return std::make_unique<MoveUpRight>();
  case 2:
    return std::make_unique<MoveDownLeft>();
  case 3:
    return std::make_unique<MoveDownRight>();
  }
  return nullptr;
}
