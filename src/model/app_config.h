#ifndef SRC_MODEL_APP_CONFIG_H_
#define SRC_MODEL_APP_CONFIG_H_

#include "cave/generator/generators.h"
#include "maze/generator/generators.h"
#include "maze/solver/solvers.h"

namespace s21 {

class AppConfig {
 public:
  AppConfig() = default;

  maze::GeneratorAlgorithm GetMazeGeneratorAlgorithm() const {
    return maze_generator_;
  }
  void SetMazeGeneratorAlgorithm(maze::GeneratorAlgorithm algorithm) {
    maze_generator_ = algorithm;
  }

  maze::SolverAlgorithm GetMazeSolverAlgorithm() const { return maze_solver_; }
  void SetMazeSolverAlgorithm(maze::SolverAlgorithm algorithm) {
    maze_solver_ = algorithm;
  }

  std::size_t GetMazeWidth() const noexcept { return maze_width_; }
  void SetMazeWidth(std::size_t maze_width) { maze_width_ = maze_width; }

  std::size_t GetMazeHeight() const noexcept { return maze_height_; }
  void SetMazeHeight(std::size_t maze_height) { maze_height_ = maze_height; }

  const Coordinate& GetMazeSolverStart() const noexcept {
    return maze_solver_start_;
  }
  void SetMazeSolverStart(Coordinate coord) { maze_solver_start_ = coord; }

  const Coordinate& GetMazeSolverEnd() const noexcept {
    return maze_solver_end_;
  }
  void SetMazeSolverEnd(Coordinate coord) { maze_solver_end_ = coord; }

  cave::GeneratorAlgorithm GetCaveGeneratorAlgorithm() const {
    return cave_generator_;
  }
  void SetCaveGeneratorAlgorithm(cave::GeneratorAlgorithm algorithm) {
    cave_generator_ = algorithm;
  }

  std::size_t GetCaveWidth() const noexcept { return cave_width_; }
  void SetCaveWidth(std::size_t cave_width) { cave_width_ = cave_width; }

  std::size_t GetCaveHeight() const noexcept { return cave_height_; }
  void SetCaveHeight(std::size_t cave_height) { cave_height_ = cave_height; }

  double GetCaveInitialChance() const noexcept { return cave_initial_chance_; }
  void SetCaveInitialChance(double initial_chance) {
    cave_initial_chance_ = initial_chance;
  }

  std::size_t GetCaveBirthLimit() const noexcept { return cave_birth_limit_; }
  void SetCaveBirthLimit(std::size_t birth_limit) {
    cave_birth_limit_ = birth_limit;
  }

  std::size_t GetCaveDeathLimit() const noexcept { return cave_death_limit_; }
  void SetCaveDeathLimit(std::size_t death_limit) {
    cave_death_limit_ = death_limit;
  }

  bool GetAutoStepEnabled() const noexcept { return is_auto_step_enabled; }
  void SetAutoStepEnabled(bool value) { is_auto_step_enabled = value; }

 private:
  maze::GeneratorAlgorithm maze_generator_ = maze::GeneratorAlgorithm::kEller;
  maze::SolverAlgorithm maze_solver_ = maze::SolverAlgorithm::kAStar;

  std::size_t maze_width_ = 4;
  std::size_t maze_height_ = 4;

  Coordinate maze_solver_start_ = {0, 0};
  Coordinate maze_solver_end_ = {1, 3};

  cave::GeneratorAlgorithm cave_generator_ = cave::GeneratorAlgorithm::kBasic;

  std::size_t cave_width_ = 50;
  std::size_t cave_height_ = 50;

  double cave_initial_chance_ = 0.45;
  std::size_t cave_birth_limit_ = 3;
  std::size_t cave_death_limit_ = 4;

  bool is_auto_step_enabled = false;
};

}  // namespace s21

#endif  // SRC_MODEL_APP_CONFIG_H_
