#include "maze_writer.h"

namespace s21 {

namespace maze {

void Writer::Write(const Maze& maze) {
  std::ofstream file(GenerateFilename(maze));
  if (file.is_open()) {
    file.clear();

    file << maze.width_ << ' ' << maze.height_ << std::endl;

    for (std::size_t i = 0; i < maze.height_; i++) {
      for (std::size_t j = 0; j < maze.width_ - 1; j++)
        file << maze.right_walls_[j][i] << ' ';
      file << maze.right_walls_[maze.width_ - 1][i] << std::endl;
    }
    file << std::endl;
    for (std::size_t i = 0; i < maze.height_; i++) {
      for (std::size_t j = 0; j < maze.width_ - 1; j++)
        file << maze.bottom_walls_[j][i] << ' ';
      file << maze.bottom_walls_[maze.width_ - 1][i] << std::endl;
    }

    file.close();
  }
}

std::string Writer::GenerateFilename(const Maze& maze) {
  std::stringstream ss;

  ss << "maze"
     << "_w" << maze.width_ << "_h" << maze.height_;

  auto time = std::time(nullptr);
  ss << "_" << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");

  ss << ".txt";

  return ss.str();
}

}  // namespace maze

}  // namespace s21
