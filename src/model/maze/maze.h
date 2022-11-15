#ifndef SRC_MODEL_MAZE_MAZE_H_
#define SRC_MODEL_MAZE_MAZE_H_

#include <array>
#include <functional>
#include <stdexcept>
#include <vector>

#include "../utils.h"

namespace s21 {

namespace maze {

class Maze {
 public:
  Maze();
  Maze(std::size_t width, std::size_t height);
  Maze(const Maze& other);
  Maze(Maze&& other);

  Maze& operator=(const Maze& other);
  Maze& operator=(Maze&& other);

  void Swap(Maze* other);

  std::size_t GetWidth() const;
  std::size_t GetHeight() const;

  void Resize(std::size_t width, std::size_t height);

  void BuildWallRight(const Coordinate& coord);
  void BuildWallLeft(const Coordinate& coord);
  void BuildWallBottom(const Coordinate& coord);
  void BuildWallTop(const Coordinate& coord);
  void DestroyWallRight(const Coordinate& coord);
  void DestroyWallLeft(const Coordinate& coord);
  void DestroyWallBottom(const Coordinate& coord);
  void DestroyWallTop(const Coordinate& coord);

  bool IsTopLeftFree(const Coordinate& coord) const;
  bool IsTopFree(const Coordinate& coord) const;
  bool IsTopRightFree(const Coordinate& coord) const;
  bool IsLeftFree(const Coordinate& coord) const;
  bool IsRightFree(const Coordinate& coord) const;
  bool IsBottomLeftFree(const Coordinate& coord) const;
  bool IsBottomFree(const Coordinate& coord) const;
  bool IsBottomRightFree(const Coordinate& coord) const;

  std::vector<Coordinate> GetNeighbors(Coordinate coord) const;

 private:
  friend class Writer;
  friend class Reader;

  void Empty();

  static const std::size_t kMinWidth = 2;
  static const std::size_t kMaxWidth = 50;
  static const std::size_t kMinHeight = 2;
  static const std::size_t kMaxHeight = 50;

  std::size_t width_;
  std::size_t height_;

  std::array<std::array<bool, kMaxHeight>, kMaxWidth> right_walls_;
  std::array<std::array<bool, kMaxHeight>, kMaxWidth> bottom_walls_;
};

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_
