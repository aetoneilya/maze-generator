#ifndef SRC_MODEL_MAZE_GENERATOR_BASE_GENERATOR_H_
#define SRC_MODEL_MAZE_GENERATOR_BASE_GENERATOR_H_

#include <cstdlib>

#include "../maze.h"

namespace s21 {

namespace maze {

class BaseGenerator {
 public:
  virtual ~BaseGenerator() = default;

  virtual Maze Generate(std::size_t width, std::size_t height) = 0;
};

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_GENERATOR_BASE_GENERATOR_H_
