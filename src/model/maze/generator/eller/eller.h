#ifndef SRC_MODEL_MAZE_GENERATOR_ELLER_ELLER_H_
#define SRC_MODEL_MAZE_GENERATOR_ELLER_ELLER_H_

#include <cstdlib>
#include <ctime>

#include "../base_generator.h"

namespace s21 {

namespace maze {

namespace generator {

class Eller : public BaseGenerator {
 public:
  Eller() = default;

  Maze Generate(std::size_t width, std::size_t height) override;
};

}  // namespace generator

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_GENERATOR_ELLER_ELLER_H_
