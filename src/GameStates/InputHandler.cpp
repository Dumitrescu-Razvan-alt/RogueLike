#include "InputHandler.h"
#include <algorithm> // For std::copy

std::unique_ptr<Command> InputHandler::HandleInput() {
  const Uint8 *currKeystate = SDL_GetKeyboardState(nullptr);
  std::unique_ptr<Command> command = nullptr;

  if (currKeystate[SDL_SCANCODE_W] && !prevKeystate[SDL_SCANCODE_W])
    command = std::make_unique<MoveUp>();
  else if (currKeystate[SDL_SCANCODE_S] && !prevKeystate[SDL_SCANCODE_S])
    command = std::make_unique<MoveDown>();
  else if (currKeystate[SDL_SCANCODE_A] && !prevKeystate[SDL_SCANCODE_A])
    command = std::make_unique<MoveLeft>();
  else if (currKeystate[SDL_SCANCODE_D] && !prevKeystate[SDL_SCANCODE_D])
    command = std::make_unique<MoveRight>();

  std::copy(currKeystate, currKeystate + SDL_NUM_SCANCODES,
            prevKeystate.begin());

  return command;
}
