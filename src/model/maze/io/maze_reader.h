#ifndef SRC_MODEL_MAZE_IO_MAZE_READER_H_
#define SRC_MODEL_MAZE_IO_MAZE_READER_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../maze.h"

namespace s21 {

namespace maze {

class Reader {
 public:
  Reader() = delete;

  friend class Maze;

  static Maze Read(const std::string& filename);
};

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_IO_MAZE_READER_H_
