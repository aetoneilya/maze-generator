#include "eller.h"

namespace s21 {

namespace maze {

namespace generator {

Maze Eller::Generate(std::size_t width, std::size_t height) {
  Maze result(width, height);
  std::vector<int> row(width);
  for (size_t i = 0; i < width; i++) {
    row[i] = (int)(i + 1);
  }
  int max_set = (int)width;
  srand((unsigned int)time(NULL));
  for (size_t j = 0; j < height; j++) {
    double rand;
    for (size_t i = 0; i < width - 1; i++) {
      rand = ((double)std::rand() / (RAND_MAX));
      if (row[i] == row[i + 1] || rand >= 0.5) {
        result.BuildWallRight(Coordinate(i, j));
      } else {
        int cur_set = row[i + 1];
        for (size_t h = 0; h < width; h++) {
          if (row[h] == cur_set) {
            row[h] = row[i];
          }
        }
      }
    }
    if (j != height - 1) {
      bool has_bottom_way = false;
      for (size_t i = 0; i < width; i++) {
        rand = ((double)std::rand() / (RAND_MAX));
        if (rand >= 0.5 && ((i != width - 1 && row[i + 1] == row[i]) ||
                            has_bottom_way == true)) {
          result.BuildWallBottom(Coordinate(i, j));
          row[i] = -row[i];
        } else {
          has_bottom_way = true;
        }
        if (i == width - 1 || row[i + 1] != abs(row[i])) {
          has_bottom_way = false;
        }
        if (row[i] < 0) {
          row[i] = ++max_set;
        }
      }
    }
  }
  for (size_t i = 0; i < width - 1; i++) {
    if (row[i] != row[i + 1] &&
        result.IsRightFree(Coordinate(i, height - 1)) == false) {
      result.DestroyWallRight(Coordinate(i, height - 1));
      int cur_set = row[i + 1];
      for (size_t j = 0; j < width; j++) {
        if (row[j] == cur_set) {
          row[j] = row[i];
        }
      }
    }
  }
  return result;
}

}  // namespace generator

}  // namespace maze

}  // namespace s21
