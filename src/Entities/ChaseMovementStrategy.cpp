#include <cmath>
#include <cstdlib>
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

struct Node {
  Position pos;
  float g, h, f;
  std::shared_ptr<Node> parent;

  Node(Position position, float g_cost = 0.0f, float h_cost = 0.0f,
       std::shared_ptr<Node> parent_node = nullptr)
      : pos(position), g(g_cost), h(h_cost), f(g_cost + h_cost),
        parent(parent_node) {}
};
struct NodeComparator {
  bool operator()(const std::shared_ptr<Node> &a,
                  const std::shared_ptr<Node> &b) const {
    return a->f > b->f;
  }
};

struct PositionHash {
    std::size_t operator()(const Position& pos) const {
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
};

class AStarPathfinder {
private:
    std::vector<std::vector<int>> map;
    int rows, cols;

    // Cardinal directions: up, down, left, right
    const std::vector<Position> cardinalDirections = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    // Diagonal directions
    const std::vector<Position> diagonalDirections = {
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
    };

    float manhattanDistance(const Position& a, const Position& b) const {
        return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y));
    }

    float diagonalDistance(const Position& a, const Position& b) const {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

    bool isValidPosition(const Position& pos) const {
        return pos.x >= 0 && pos.x < cols && pos.y >= 0 && pos.y < rows && map[pos.y][pos.x] == 0;
    }

    Position findNextMove(const Position& enemyPos, const Position& playerPos,
                         const std::vector<Position>& directions,
                         bool isDiagonal) const {

        // If already at player position, stay put
        if (enemyPos == playerPos) {
            return enemyPos;
        }

        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator> openSet;
        std::unordered_set<Position, PositionHash> closedSet;

        float initialH = isDiagonal ? diagonalDistance(enemyPos, playerPos) : manhattanDistance(enemyPos, playerPos);
        auto startNode = std::make_shared<Node>(enemyPos, 0.0f, initialH);

        openSet.push(startNode);

        while (!openSet.empty()) {
            auto current = openSet.top();
            openSet.pop();

            if (current->pos == playerPos) {
                // Found path - trace back to get first move
                auto node = current;
                while (node->parent && node->parent->parent) {
                    node = node->parent;
                }
                return node->pos;
            }

            closedSet.insert(current->pos);

            // Check all valid neighbors
            for (const auto& dir : directions) {
                Position newPos(current->pos.x + dir.x, current->pos.y + dir.y);

                if (!isValidPosition(newPos) || closedSet.count(newPos)) {
                    continue;
                }

                float g = current->g + (isDiagonal ? std::sqrt(2.0f) : 1.0f);
                float h = isDiagonal ? diagonalDistance(newPos, playerPos) : manhattanDistance(newPos, playerPos);

                auto neighbor = std::make_shared<Node>(newPos, g, h, current);
                openSet.push(neighbor);
            }
        }

        return Position(-1, -1); // No path found
    }

public:
    AStarPathfinder(const std::vector<std::vector<int>>& matrix)
        : map(matrix), rows(matrix.size()), cols(matrix[0].size()) {}

    void updateMatrix(const std::vector<std::vector<int>>& matrix) {
        map = matrix;
        rows = matrix.size();
        cols = matrix[0].size();
    }

    /**
     * Get next best cardinal move for enemy to reach player
     * @param enemyPos Enemy position
     * @param playerPos Player position
     * @return Next move position or (-1, -1) if no path
     */
    Position getNextCardinalMove(const Position& enemyPos, const Position& playerPos) const {
        return findNextMove(enemyPos, playerPos, cardinalDirections, false);
    }

    /**
     * Get next best diagonal move for enemy to reach player
     * @param enemyPos Enemy position
     * @param playerPos Player position
     * @return Next move position or (-1, -1) if no path
     */
    Position getNextDiagonalMove(const Position& enemyPos, const Position& playerPos) const {
        return findNextMove(enemyPos, playerPos, diagonalDirections, true);
    }
};
