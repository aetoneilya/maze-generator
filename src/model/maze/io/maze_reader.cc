#include "maze_reader.h"

namespace s21 {

namespace maze {

Maze Reader::Read(const std::string& filename) {
  Maze maze;

  std::ifstream file(filename);
  if (file.is_open()) {
    file >> maze.width_ >> maze.height_;

    if (maze.width_ >= Maze::kMinWidth && maze.width_ <= Maze::kMaxWidth &&
        maze.height_ >= Maze::kMinHeight && maze.height_ <= Maze::kMaxHeight) {
      for (std::size_t i = 0; i < maze.height_; i++) {
        for (std::size_t j = 0; j < maze.width_; j++)
          file >> maze.right_walls_[j][i];
      }
      for (std::size_t i = 0; i < maze.height_; i++) {
        for (std::size_t j = 0; j < maze.width_; j++)
          file >> maze.bottom_walls_[j][i];
      }
    } else {
      throw std::runtime_error("ошибка чтения");
    }

    file.close();
  } else {
    throw std::runtime_error("файл не найден");
  }

  return maze;
}

}  // namespace maze

}  // namespace s21
