#include "model.h"

namespace s21 {

const AppConfig& Model::GetCAppConfig() const { return app_; }

AppConfig* Model::GetAppConfig() { return &app_; }

std::reference_wrapper<const maze::Maze> Model::GetMaze() const {
  return std::cref(maze_);
}

void Model::SetMazeGenerator(maze::GeneratorAlgorithm algorithm) {
  switch (algorithm) {
    case maze::GeneratorAlgorithm::kEller:
      maze_generator_ = std::make_unique<maze::generator::Eller>();
      break;
  }
}

void Model::GenerateMaze(std::size_t width, std::size_t height) {
  maze_ = maze_generator_->Generate(width, height);
}

void Model::SetMazeSolver(maze::SolverAlgorithm algorithm) {
  switch (algorithm) {
    case maze::SolverAlgorithm::kAStar:
      maze_solver_ = std::make_unique<maze::solver::AStar>();
      break;
  }
}

void Model::SolveMaze(const Coordinate& start, const Coordinate& end) {
  maze_solver_->Build(GetMaze());
  maze_solver_->Solve(start, end);
}

std::reference_wrapper<const maze::Solution> Model::GetMazeSolution() const {
  return std::cref(maze_solver_->GetSolution());
}

void Model::ReadMaze(const std::string& filename,
                     std::function<void(const std::string&)> error_callback) {
  try {
    auto maze = maze::Reader::Read(filename);
    maze_.Swap(&maze);
  } catch (const std::exception& e) {
    if (error_callback) error_callback(e.what());
    if (maze_generator_)
      GenerateMaze(app_.GetMazeWidth(), app_.GetMazeHeight());
  }
}

void Model::WriteMaze() const { maze::Writer::Write(maze_); }

void Model::SetCaveGenerator(cave::GeneratorAlgorithm algorithm) {
  switch (algorithm) {
    case cave::GeneratorAlgorithm::kBasic:
      cave_generator_ = std::make_unique<cave::generator::Basic>();
      break;
  }
}

void Model::GenerateCave(std::size_t width, std::size_t height) {
  if (cave_generator_) cave_ = cave_generator_->Generate(width, height);
}

void Model::SetCaveSimulationStep(std::size_t steps) {
  cave_ = cave_generator_->Step(steps);
}

void Model::SetCaveInitialChance(double chance) {
  cave_generator_->SetInitialChance(static_cast<int>(chance * 100));
}

void Model::SetCaveBirthLimit(std::size_t birth_limit) {
  cave_generator_->SetBirthLimit(static_cast<int>(birth_limit));
}

void Model::SetCaveDeathLimit(std::size_t death_limit) {
  cave_generator_->SetBirthLimit(static_cast<int>(death_limit));
}

std::reference_wrapper<const cave::Cave> Model::GetCave() const {
  return cave_;
}

void Model::ReadCave(const std::string& filename,
                     std::function<void(const std::string&)> error_callback) {
  try {
    auto cave = cave::Reader::Read(filename);
    cave_.Swap(&cave);
  } catch (const std::exception& e) {
    if (error_callback) error_callback(e.what());
    if (cave_generator_)
      GenerateCave(app_.GetCaveWidth(), app_.GetCaveHeight());
  }
}

void Model::WriteCave() const { cave::Writer::Write(cave_); }

}  // namespace s21
