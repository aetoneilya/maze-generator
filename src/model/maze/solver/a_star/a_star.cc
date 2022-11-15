#include "a_star.h"

namespace s21 {

namespace maze {

namespace solver {

void AStar::Build(const Maze& maze) {
  solution_.clear();

  graph_.resize(maze.GetHeight());
  for (std::size_t i = 0; i < maze.GetHeight(); i++) {
    graph_[i].resize(maze.GetWidth());
  }

  for (std::size_t i = 0; i < maze.GetHeight(); i++) {
    for (std::size_t j = 0; j < maze.GetWidth(); j++) {
      graph_[i][j].Clear();

      graph_[i][j].SetCoordinate(j, i);

      for (const auto& neighbor : maze.GetNeighbors({j, i})) {
        graph_[i][j].neighbors_.push_back(&graph_[neighbor.y][neighbor.x]);
      }
    }
  }
}

void AStar::Solve(const Coordinate& start, const Coordinate& end) {
  solution_.clear();

  std::list<Node*> open = {&graph_[start.y][start.x]};
  std::unordered_set<Node*, Node::Hash> closed;

  struct {
    Node* current;
    Node* target;
  } node = {open.front(), &graph_[end.y][end.x]};

  while (open.size() > 0) {
    node.current = open.front();

    for (auto it = std::next(open.begin()); it != open.end(); it++) {
      if ((*it)->GetFCost() < node.current->GetFCost() ||
          ((*it)->GetFCost() == node.current->GetFCost() &&
           (*it)->GetHCost() < node.current->GetHCost())) {
        node.current = *it;
      }
    }

    open.remove(node.current);
    closed.insert(node.current);

    if (node.current == node.target) {
      BuildPath(graph_[start.y][start.x], *node.target);
      return;
    }

    for (auto neighbor : node.current->GetNeighbors()) {
      if (closed.find(neighbor) != closed.end()) continue;

      std::size_t new_movement_cost_to_neighbor =
          node.current->GetGCost() + GetDistance(*node.current, *neighbor);
      if (new_movement_cost_to_neighbor < neighbor->GetGCost() ||
          std::find(open.begin(), open.end(), neighbor) == open.end()) {
        neighbor->g_cost_ = new_movement_cost_to_neighbor;
        neighbor->h_cost_ = GetDistance(*neighbor, *node.target);

        neighbor->parent_ = node.current;

        if (std::find(open.begin(), open.end(), neighbor) == open.end()) {
          open.push_back(neighbor);
        }
      }
    }
  }
}

std::size_t AStar::GetDistance(const Node& start, const Node& end) const {
  std::size_t dist_x = start.GetCoordinate().x - end.GetCoordinate().x;
  std::size_t dist_y = start.GetCoordinate().y - end.GetCoordinate().y;
  return (dist_x > dist_y) ? 14 * dist_y + 10 * (dist_x - dist_y)
                           : 14 * dist_x + 10 * (dist_y - dist_x);
}

void AStar::BuildPath(const Node& start, const Node& end) {
  Node current = end;

  while (current != start) {
    solution_.push_back(current.GetCoordinate());
    current = *current.parent_;
  }
  solution_.push_back(start.GetCoordinate());
  solution_.reverse();
}

AStar::Node::Node(std::size_t x, std::size_t y) noexcept : coord_({x, y}) {}

AStar::Node::Node(const Coordinate& coord) noexcept : coord_(coord) {}

bool AStar::Node::operator==(const Node& node) const noexcept {
  return coord_.x == node.coord_.x && coord_.y == node.coord_.y;
}

bool AStar::Node::operator!=(const Node& node) const noexcept {
  return !operator==(node);
}

void AStar::Node::Clear() {
  neighbors_.clear();

  parent_ = nullptr;

  g_cost_ = 0;
  h_cost_ = 0;

  coord_ = {0, 0};
}

const std::vector<AStar::Node*>& AStar::Node::GetNeighbors() const noexcept {
  return neighbors_;
}

std::size_t AStar::Node::GetGCost() const noexcept { return g_cost_; }

std::size_t AStar::Node::GetHCost() const noexcept { return h_cost_; }

std::size_t AStar::Node::GetFCost() const noexcept { return g_cost_ + h_cost_; }

Coordinate AStar::Node::GetCoordinate() const noexcept { return coord_; }

void AStar::Node::SetCoordinate(const Coordinate& coord) { coord_ = coord; }

void AStar::Node::SetCoordinate(std::size_t x, std::size_t y) {
  coord_ = {x, y};
}

std::size_t AStar::Node::Hash::operator()(Node* node) const noexcept {
  std::size_t x_hash = std::hash<std::size_t>{}(node->coord_.x);
  std::size_t y_hash = std::hash<std::size_t>{}(node->coord_.y) << 1;
  return x_hash ^ y_hash;
}

}  // namespace solver

}  // namespace maze

}  // namespace s21
