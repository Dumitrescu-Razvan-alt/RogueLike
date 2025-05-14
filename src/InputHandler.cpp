#include "InputHandler.h"

std::unique_ptr<Command> InputHandler::HandleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: return std::make_unique<MoveUp>();
            case SDLK_s: return std::make_unique<MoveDown>();
            case SDLK_a: return std::make_unique<MoveLeft>();
            case SDLK_d: return std::make_unique<MoveRight>();
            default: break;
        }
    }
    return nullptr;
}
