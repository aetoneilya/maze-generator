#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <memory>
#include <string>

#include "app_config.h"
#include "cave/cave.h"
#include "cave/generator/generators.h"
#include "cave/io/cave_reader.h"
#include "cave/io/cave_writer.h"
#include "maze/generator/generators.h"
#include "maze/io/maze_reader.h"
#include "maze/io/maze_writer.h"
#include "maze/maze.h"
#include "maze/solver/solvers.h"
#include "utils.h"

namespace s21 {

class Model {
 public:
  Model() = default;

  const AppConfig& GetCAppConfig() const;
  AppConfig* GetAppConfig();

  void SetMazeGenerator(maze::GeneratorAlgorithm algorithm);
  void GenerateMaze(std::size_t width, std::size_t height);
  std::reference_wrapper<const maze::Maze> GetMaze() const;

  void SetMazeSolver(maze::SolverAlgorithm algorithm);
  void SolveMaze(const Coordinate& start, const Coordinate& end);
  std::reference_wrapper<const maze::Solution> GetMazeSolution() const;

  void ReadMaze(const std::string& filename,
                std::function<void(const std::string&)> error_callback);
  void WriteMaze() const;

  void SetCaveGenerator(cave::GeneratorAlgorithm algorithm);
  void GenerateCave(std::size_t width, std::size_t height);
  void SetCaveSimulationStep(std::size_t steps);
  void SetCaveInitialChance(double chance);
  void SetCaveBirthLimit(std::size_t birth_limit);
  void SetCaveDeathLimit(std::size_t death_limit);
  std::reference_wrapper<const cave::Cave> GetCave() const;

  void ReadCave(const std::string& filename,
                std::function<void(const std::string&)> error_callback);
  void WriteCave() const;

 private:
  AppConfig app_;

  maze::Maze maze_;
  std::unique_ptr<maze::BaseGenerator> maze_generator_;
  std::unique_ptr<maze::BaseSolver> maze_solver_;

  cave::Cave cave_;
  std::unique_ptr<cave::generator::Basic> cave_generator_;
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
