// AStarMovementStrategy.h
#pragma once
#include "Map.h"
#include "MovementStrategy.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_set>
#include <vector>

struct Position {
  int x, y;

  Position(int x = 0, int y = 0) : x(x), y(y) {}

  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }
};

struct AStarNode {
  Position pos;
  float g, h, f;
  std::shared_ptr<AStarNode> parent;

  AStarNode(Position position, float g_cost = 0.0f, float h_cost = 0.0f,
            std::shared_ptr<AStarNode> parent_node = nullptr)
      : pos(position), g(g_cost), h(h_cost), f(g_cost + h_cost),
        parent(parent_node) {}
};

struct NodeComparator {
  bool operator()(const std::shared_ptr<AStarNode> &a,
                  const std::shared_ptr<AStarNode> &b) const {
    return a->f > b->f;
  }
};

struct PositionHash {
  std::size_t operator()(const Position &pos) const {
    return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
  }
};

// A* Cardinal Movement Strategy (replaces NormalMovement)
class AStarCardinalMovement : public MovementStrategy {
private:
  Map &map;
  Player &player;

  const std::vector<Position> directions = {
      {0, -1}, {0, 1}, {-1, 0}, {1, 0} // up, down, left, right
  };

  float manhattanDistance(const Position &a, const Position &b) const {
    return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y));
  }

  Position findNextMove(const Position &enemyPos,
                        const Position &playerPos) const {
    if (enemyPos == playerPos) {
      return enemyPos;
    }

    std::priority_queue<std::shared_ptr<AStarNode>,
                        std::vector<std::shared_ptr<AStarNode>>, NodeComparator>
        openSet;
    std::unordered_set<Position, PositionHash> closedSet;

    auto startNode = std::make_shared<AStarNode>(
        enemyPos, 0.0f, manhattanDistance(enemyPos, playerPos));
    openSet.push(startNode);

    while (!openSet.empty()) {
      auto current = openSet.top();
      openSet.pop();

      if (current->pos == playerPos) {
        // Found path - get first move
        auto node = current;
        while (node->parent && node->parent->parent) {
          node = node->parent;
        }
        return node->pos;
      }

      closedSet.insert(current->pos);

      for (const auto &dir : directions) {
        Position newPos(current->pos.x + dir.x, current->pos.y + dir.y);

        if (!map.IsWalkable(newPos.x, newPos.y) || closedSet.count(newPos)) {
          continue;
        }

        float g = current->g + 1.0f;
        float h = manhattanDistance(newPos, playerPos);
        auto neighbor = std::make_shared<AStarNode>(newPos, g, h, current);

        openSet.push(neighbor);
      }
    }

    return Position(-1, -1); // No path found
  }

public:
  AStarCardinalMovement(Map &gameMap, Player &gamePlayer)
      : map(gameMap), player(gamePlayer) {}

  std::unique_ptr<Command> CalculateCommand(int &dx, int &dy) override {
    Position enemyPos(dx, dy); // Current enemy position will be passed in
    Position playerPos(player.GetX(), player.GetY());
    std::cout<<player.GetX() << " " << player.GetY() << "\n";

    Position nextMove = findNextMove(enemyPos, playerPos);

    if (nextMove.x == -1 && nextMove.y == -1) {
      // No path found, stay still
      return nullptr;
    }

    // Calculate direction
    int moveX = nextMove.x - enemyPos.x;
    int moveY = nextMove.y - enemyPos.y;

    // Return appropriate command
    if (moveY == -1)
      return std::make_unique<MoveUp>();
    if (moveY == 1)
      return std::make_unique<MoveDown>();
    if (moveX == -1)
      return std::make_unique<MoveLeft>();
    if (moveX == 1)
      return std::make_unique<MoveRight>();

    return nullptr;
  }
};

// A* Diagonal Movement Strategy (replaces DiagonalMovement)
class AStarDiagonalMovement : public MovementStrategy {
private:
  Map &map;
  Player &player;

  const std::vector<Position> directions = {
      {-1, -1}, {1, -1}, {-1, 1}, {1, 1} // diagonal directions
  };

  float diagonalDistance(const Position &a, const Position &b) const {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
  }

  Position findNextMove(const Position &enemyPos,
                        const Position &playerPos) const {
    if (enemyPos == playerPos) {
      return enemyPos;
    }

    std::priority_queue<std::shared_ptr<AStarNode>,
                        std::vector<std::shared_ptr<AStarNode>>, NodeComparator>
        openSet;
    std::unordered_set<Position, PositionHash> closedSet;

    auto startNode = std::make_shared<AStarNode>(
        enemyPos, 0.0f, diagonalDistance(enemyPos, playerPos));
    openSet.push(startNode);

    while (!openSet.empty()) {
      auto current = openSet.top();
      openSet.pop();

      if (current->pos == playerPos) {
        // Found path - get first move
        auto node = current;
        while (node->parent && node->parent->parent) {
          node = node->parent;
        }
        return node->pos;
      }

      closedSet.insert(current->pos);

      for (const auto &dir : directions) {
        Position newPos(current->pos.x + dir.x, current->pos.y + dir.y);

        if (!map.IsWalkable(newPos.x, newPos.y) || closedSet.count(newPos)) {
          continue;
        }

        float g = current->g + std::sqrt(2.0f);
        float h = diagonalDistance(newPos, playerPos);
        auto neighbor = std::make_shared<AStarNode>(newPos, g, h, current);

        openSet.push(neighbor);
      }
    }

    return Position(-1, -1); // No path found
  }

public:
  AStarDiagonalMovement(Map &gameMap, Player &gamePlayer)
      : map(gameMap), player(gamePlayer) {}

  std::unique_ptr<Command> CalculateCommand(int &dx, int &dy) override {
    Position enemyPos(dx, dy); // Current enemy position will be passed in
    Position playerPos(player.GetX(), player.GetY());

    Position nextMove = findNextMove(enemyPos, playerPos);

    if (nextMove.x == -1 && nextMove.y == -1) {
      // No path found, stay still
      return nullptr;
    }

    // Calculate direction
    int moveX = nextMove.x - enemyPos.x;
    int moveY = nextMove.y - enemyPos.y;

    // Return appropriate diagonal command
    if (moveX == -1 && moveY == -1)
      return std::make_unique<MoveUpLeft>();
    if (moveX == 1 && moveY == -1)
      return std::make_unique<MoveUpRight>();
    if (moveX == -1 && moveY == 1)
      return std::make_unique<MoveDownLeft>();
    if (moveX == 1 && moveY == 1)
      return std::make_unique<MoveDownRight>();

    return nullptr;
  }
};
