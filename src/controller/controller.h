#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Model* model);

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
  Model* model_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
