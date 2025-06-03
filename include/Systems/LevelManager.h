#include "Map.h"
class LevelManager {
public:
  Map &GetCurrentMap() { return *current_map_; }
  void LoadLevel(std::unique_ptr<Map> new_map) {
    current_map_ = std::move(new_map);
  }

private:
  std::unique_ptr<Map> current_map_;
};
