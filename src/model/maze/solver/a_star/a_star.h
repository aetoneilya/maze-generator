#ifndef SRC_MODEL_MAZE_SOLVER_A_STAR_A_STAR_H_
#define SRC_MODEL_MAZE_SOLVER_A_STAR_A_STAR_H_

#include <functional>
// #include <iostream>
#include <list>
#include <unordered_set>
#include <vector>

#include "../base_solver.h"

namespace s21 {

namespace maze {

namespace solver {

class AStar : public BaseSolver {
 public:
  class Node;

  AStar() = default;

  void Build(const Maze& maze) override;
  void Solve(const Coordinate& start, const Coordinate& end) override;

 private:
  std::size_t GetDistance(const Node& start, const Node& end) const;
  void BuildPath(const Node& start, const Node& end);

  std::vector<std::vector<Node>> graph_;
};

class AStar::Node {
 public:
  friend class AStar;

  class Hash;

  Node() noexcept = default;
  Node(std::size_t x, std::size_t y) noexcept;
  explicit Node(const Coordinate& coord) noexcept;

  bool operator==(const Node& node) const noexcept;
  bool operator!=(const Node& node) const noexcept;

  void Clear();

  const std::vector<Node*>& GetNeighbors() const noexcept;

  std::size_t GetGCost() const noexcept;
  std::size_t GetHCost() const noexcept;
  std::size_t GetFCost() const noexcept;

  Coordinate GetCoordinate() const noexcept;

 private:
  void SetCoordinate(const Coordinate& coord);
  void SetCoordinate(std::size_t x, std::size_t y);

  std::vector<Node*> neighbors_;

  Node* parent_ = nullptr;

  std::size_t g_cost_ = 0;
  std::size_t h_cost_ = 0;

  Coordinate coord_ = {0, 0};
};

class AStar::Node::Hash {
 public:
  std::size_t operator()(Node* node) const noexcept;
};

}  // namespace solver

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_SOLVER_A_STAR_A_STAR_H_
