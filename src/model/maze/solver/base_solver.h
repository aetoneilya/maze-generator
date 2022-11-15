#ifndef SRC_MODEL_MAZE_SOLVER_BASE_SOLVER_H_
#define SRC_MODEL_MAZE_SOLVER_BASE_SOLVER_H_

#include <list>

#include "../../utils.h"
#include "../maze.h"

namespace s21 {

namespace maze {

using Solution = std::list<Coordinate>;

class BaseSolver {
 public:
  virtual ~BaseSolver() = default;

  virtual void Build(const Maze& maze) = 0;

  virtual void Solve(const Coordinate& start, const Coordinate& end) = 0;
  std::reference_wrapper<const Solution> GetSolution() const {
    return std::cref(solution_);
  }

 protected:
  Solution solution_;
};

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_SOLVER_BASE_SOLVER_H_
