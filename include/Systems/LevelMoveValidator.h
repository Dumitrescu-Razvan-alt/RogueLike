#include "Entity.h"
#include "LevelManager.h"
class IMoveValidator {
public:
  virtual ~IMoveValidator() = default;
  virtual bool CanMoveTo(const Entity &entity, int dx, int dy) const = 0;
};

class LevelMoveValidator : public IMoveValidator {
public:
  explicit LevelMoveValidator(LevelManager &level_manager)
      : level_manager_(level_manager) {}

  bool CanMoveTo(const Entity &entity, int dx, int dy) const override {
    const Map &current_map = level_manager_.GetCurrentMap();
    const int new_x = entity.GetX() + dx;
    const int new_y = entity.GetY() + dy;
    return current_map.IsWalkable(new_x, new_y);
  }

private:
  LevelManager &level_manager_;
};
