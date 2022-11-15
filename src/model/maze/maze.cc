#include "maze.h"

namespace s21 {

namespace maze {

Maze::Maze() : Maze(kMaxWidth, kMaxHeight) {}

Maze::Maze(std::size_t width, std::size_t height)
    : width_(width), height_(height) {
  if (width > kMaxWidth || height > kMaxHeight) {
    throw std::invalid_argument("некорректный размер лабиринта");
  }
  Empty();
}

Maze::Maze(const Maze& other)
    : width_(other.width_),
      height_(other.height_),
      right_walls_(other.right_walls_),
      bottom_walls_(other.bottom_walls_) {}

Maze::Maze(Maze&& other) { Swap(&other); }

Maze& Maze::operator=(const Maze& other) {
  if (this != &other) {
    Maze(other).Swap(this);
  }
  return *this;
}

Maze& Maze::operator=(Maze&& other) {
  if (this != &other) {
    Maze(std::move(other)).Swap(this);
  }
  return *this;
}

void Maze::Swap(Maze* other) {
  std::swap(width_, other->width_);
  std::swap(height_, other->height_);

  std::swap(right_walls_, other->right_walls_);
  std::swap(bottom_walls_, other->bottom_walls_);
}

std::size_t Maze::GetWidth() const { return width_; }

std::size_t Maze::GetHeight() const { return height_; }

void Maze::Resize(std::size_t width, std::size_t height) {
  if (width > kMaxWidth || height > kMaxHeight) {
    throw std::invalid_argument("некорректный размер лабиринта");
  }

  for (std::size_t i = 0; i < width_; i++) {
    bottom_walls_.at(i).at(height_ - 1) = false;
  }
  for (size_t j = 0; j < height_; j++) {
    right_walls_.at(width_ - 1).at(j) = false;
  }

  width_ = width;
  height_ = height;

  for (size_t i = 0; i < width_; i++) {
    bottom_walls_.at(i).at(height_ - 1) = true;
  }
  for (size_t j = 0; j < height_; j++) {
    right_walls_.at(width_ - 1).at(j) = true;
  }
}

void Maze::BuildWallRight(const Coordinate& coord) {
  right_walls_.at(coord.x).at(coord.y) = true;
}

void Maze::BuildWallLeft(const Coordinate& coord) {
  if (coord.x != 0) right_walls_.at(coord.x - 1).at(coord.y) = true;
}

void Maze::BuildWallBottom(const Coordinate& coord) {
  bottom_walls_.at(coord.x).at(coord.y) = true;
}

void Maze::BuildWallTop(const Coordinate& coord) {
  if (coord.y != 0) bottom_walls_.at(coord.x).at(coord.y - 1) = true;
}

void Maze::DestroyWallRight(const Coordinate& coord) {
  if (coord.x != width_ - 1) right_walls_.at(coord.x).at(coord.y) = false;
}

void Maze::DestroyWallLeft(const Coordinate& coord) {
  if (coord.x != 0) right_walls_.at(coord.x - 1).at(coord.y) = false;
}

void Maze::DestroyWallBottom(const Coordinate& coord) {
  if (coord.y != height_ - 1) bottom_walls_.at(coord.x).at(coord.y) = false;
}

void Maze::DestroyWallTop(const Coordinate& coord) {
  if (coord.y != 0) bottom_walls_.at(coord.x).at(coord.y - 1) = false;
}

bool Maze::IsTopLeftFree(const Coordinate& coord) const {
  return (IsTopFree(coord) && IsLeftFree({coord.x, coord.y - 1})) &&
         (IsLeftFree(coord) && IsTopFree({coord.x - 1, coord.y}));
}

bool Maze::IsTopFree(const Coordinate& coord) const {
  return !(coord.y == 0) && !bottom_walls_.at(coord.x).at(coord.y - 1);
}

bool Maze::IsTopRightFree(const Coordinate& coord) const {
  return (IsTopFree(coord) && IsRightFree({coord.x, coord.y - 1})) ||
         (IsRightFree(coord) && IsTopFree({coord.x + 1, coord.y}));
}

bool Maze::IsLeftFree(const Coordinate& coord) const {
  return !(coord.x == 0) && !right_walls_.at(coord.x - 1).at(coord.y);
}

bool Maze::IsRightFree(const Coordinate& coord) const {
  return coord.x + 1 < width_ && !right_walls_.at(coord.x).at(coord.y);
}

bool Maze::IsBottomLeftFree(const Coordinate& coord) const {
  return (IsBottomFree(coord) && IsLeftFree({coord.x, coord.y + 1})) ||
         (IsLeftFree(coord) && IsBottomFree({coord.x - 1, coord.y}));
}

bool Maze::IsBottomFree(const Coordinate& coord) const {
  return coord.y + 1 < height_ && !bottom_walls_.at(coord.x).at(coord.y);
}

bool Maze::IsBottomRightFree(const Coordinate& coord) const {
  return (IsBottomFree(coord) && IsRightFree({coord.x, coord.y + 1})) ||
         (IsRightFree(coord) && IsBottomFree({coord.x + 1, coord.y}));
}

std::vector<Coordinate> Maze::GetNeighbors(Coordinate coord) const {
  std::vector<Coordinate> neighbors;

  if (IsTopFree(coord)) neighbors.emplace_back(coord.x, coord.y - 1);
  if (IsLeftFree(coord)) neighbors.emplace_back(coord.x - 1, coord.y);
  if (IsRightFree(coord)) neighbors.emplace_back(coord.x + 1, coord.y);
  if (IsBottomFree(coord)) neighbors.emplace_back(coord.x, coord.y + 1);

  return neighbors;
}

void Maze::Empty() {
  for (std::size_t i = 0; i < kMaxWidth - 1; i++) {
    for (std::size_t j = 0; j < kMaxHeight; j++) {
      right_walls_[i][j] = 0;
      bottom_walls_[i][j] = 0;
    }
    bottom_walls_[i][kMaxHeight - 1] = 1;
  }
  for (std::size_t j = 0; j < kMaxHeight; j++) {
    right_walls_[kMaxWidth - 1][j] = 1;
    bottom_walls_[kMaxWidth - 1][j] = 0;
  }
  for (size_t i = 0; i < width_; i++) {
    bottom_walls_[i][height_ - 1] = 1;
  }
  for (size_t j = 0; j < height_; j++) {
    right_walls_[width_ - 1][j] = 1;
  }
}

}  // namespace maze

}  // namespace s21
