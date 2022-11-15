#ifndef SRC_MODEL_MAZE_IO_MAZE_WRITER_H_
#define SRC_MODEL_MAZE_IO_MAZE_WRITER_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../maze.h"

namespace s21 {

namespace maze {

class Writer {
 public:
  Writer() = delete;

  static void Write(const Maze& maze);

 private:
  static std::string GenerateFilename(const Maze& maze);
};

}  // namespace maze

}  // namespace s21

#endif  // SRC_MODEL_MAZE_IO_MAZE_WRITER_H_
