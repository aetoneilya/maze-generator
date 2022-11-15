#ifndef SRC_MODEL_CAVE_GENERATOR_BASIC_BASIC_H_
#define SRC_MODEL_CAVE_GENERATOR_BASIC_BASIC_H_

#include <array>
#include <ctime>
#include <stdexcept>

#include "../../cave.h"

namespace s21 {

namespace cave {

namespace generator {

class Basic {
 public:
  Basic() = default;

  void SetCave(const Cave& cave);

  int GetInitialChance() const;
  void SetInitialChance(int init_chance);

  int GetBirthLimit() const;
  void SetBirthLimit(int bl);

  int GetDeathLimit() const;
  void SetDeathLimit(int dl);

  Cave Generate(std::size_t width, std::size_t height);
  Cave Step(std::size_t steps);
  std::size_t GetStep() const;

 private:
  void CellularAutomataStep();
  int CountAliveNeighbors(std::size_t i, std::size_t j);

  std::size_t step_ = 0;

  int initial_chance_ = 45;

  int birth_limit_ = 4;
  int death_limit_ = 3;

  Cave cave_;
  Cave cave_buff_;
};

}  // namespace generator

}  // namespace cave

}  // namespace s21

#endif  // SRC_MODEL_CAVE_GENERATOR_BASIC_BASIC_H_
