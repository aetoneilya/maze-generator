#include "basic.h"

namespace s21 {

namespace cave {

namespace generator {

void Basic::SetCave(const Cave& cave) { cave_ = cave; }

int Basic::GetInitialChance() const { return initial_chance_; }

void Basic::SetInitialChance(int init_chance) { initial_chance_ = init_chance; }

int Basic::GetBirthLimit() const { return birth_limit_; }

void Basic::SetBirthLimit(int bl) {
  if (bl < 0 || bl > 7) {
    throw std::invalid_argument("Birth limit must be value from 0 to 7");
  }
  birth_limit_ = bl;
}

int Basic::GetDeathLimit() const { return death_limit_; }

void Basic::SetDeathLimit(int dl) {
  if (dl < 0 || dl > 7) {
    throw std::invalid_argument("Death limit must be value from 0 to 7");
  }
  death_limit_ = dl;
}

Cave Basic::Generate(std::size_t width, std::size_t height) {
  cave_.Resize(width, height);

  unsigned int seed = (unsigned int)time(NULL);
  for (std::size_t i = 0; i < cave_.width_; i++) {
    for (std::size_t j = 0; j < cave_.height_; j++) {
      cave_.cave_[i][j] = rand_r(&seed) % 100 < initial_chance_;
    }
  }

  return cave_;
}

std::size_t Basic::GetStep() const { return step_; }

Cave Basic::Step(std::size_t steps) {
  for (std::size_t i = 0; i < steps; i++) {
    CellularAutomataStep();
    std::swap(cave_.cave_, cave_buff_.cave_);
    step_++;
  }
  return cave_;
}

void Basic::CellularAutomataStep() {
  for (std::size_t x = 0; x < cave_.width_; x++)
    for (std::size_t y = 0; y < cave_.height_; y++) {
      int live_count = CountAliveNeighbors(x, y);
      if (cave_.cave_[x][y]) {
        if (live_count < death_limit_)
          cave_buff_.cave_[x][y] = false;
        else
          cave_buff_.cave_[x][y] = true;

      } else {
        if (live_count > birth_limit_)
          cave_buff_.cave_[x][y] = true;
        else
          cave_buff_.cave_[x][y] = false;
      }
    }
}

int Basic::CountAliveNeighbors(std::size_t x, std::size_t y) {
  int count = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      size_t neighbour_x = x + i;
      size_t neighbour_y = y + j;

      if (i == 0 && j == 0) {
      } else if (neighbour_x >= cave_.width_ || neighbour_y >= cave_.height_ ||
                 (x == 0 && i == -1) || (y == 0 && j == -1)) {
        count = count + 1;
      } else if (cave_.cave_[neighbour_x][neighbour_y]) {
        count = count + 1;
      }
    }
  }
  return count;
}

}  // namespace generator

}  // namespace cave

}  // namespace s21
