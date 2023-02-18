#include "controller.h"

namespace s21 {

Controller::Controller(Model* model) : model_(model) {}

const AppConfig& Controller::GetCAppConfig() const {
  return model_->GetCAppConfig();
}

AppConfig* Controller::GetAppConfig() { return model_->GetAppConfig(); }

void Controller::SetMazeGenerator(maze::GeneratorAlgorithm algorithm) {
  model_->SetMazeGenerator(algorithm);
}

void Controller::GenerateMaze(std::size_t width, std::size_t height) {
  model_->GenerateMaze(width, height);
}

std::reference_wrapper<const maze::Maze> Controller::GetMaze() const {
  return model_->GetMaze();
}

void Controller::SetMazeSolver(maze::SolverAlgorithm algorithm) {
  model_->SetMazeSolver(algorithm);
}

void Controller::SolveMaze(const Coordinate& start, const Coordinate& end) {
  model_->SolveMaze(start, end);
}

std::reference_wrapper<const maze::Solution> Controller::GetMazeSolution()
    const {
  return model_->GetMazeSolution();
}

void Controller::ReadMaze(
    const std::string& filename,
    std::function<void(const std::string&)> error_callback) {
  model_->ReadMaze(filename, error_callback);
}

void Controller::WriteMaze() const { model_->WriteMaze(); }

void Controller::SetCaveGenerator(cave::GeneratorAlgorithm algorithm) {
  model_->SetCaveGenerator(algorithm);
}

void Controller::GenerateCave(std::size_t width, std::size_t height) {
  model_->GenerateCave(width, height);
}

void Controller::SetCaveSimulationStep(std::size_t steps) {
  model_->SetCaveSimulationStep(steps);
}

void Controller::SetCaveInitialChance(double chance) {
  model_->SetCaveInitialChance(chance);
}

void Controller::SetCaveBirthLimit(std::size_t birth_limit) {
  model_->SetCaveBirthLimit(birth_limit);
}

void Controller::SetCaveDeathLimit(std::size_t death_limit) {
  model_->SetCaveDeathLimit(death_limit);
}

std::reference_wrapper<const cave::Cave> Controller::GetCave() const {
  return model_->GetCave();
}

void Controller::ReadCave(
    const std::string& filename,
    std::function<void(const std::string&)> error_callback) {
  model_->ReadCave(filename, error_callback);
}

void Controller::WriteCave() const { model_->WriteCave(); }

}  // namespace s21
