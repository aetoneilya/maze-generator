#ifndef SRC_MODEL_CAVE_IO_CAVE_READER_H_
#define SRC_MODEL_CAVE_IO_CAVE_READER_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../cave.h"

namespace s21 {

namespace cave {

class Reader {
 public:
  Reader() = delete;

  friend class Cave;

  static Cave Read(const std::string& filename);
};

}  // namespace cave

}  // namespace s21

#endif  // SRC_MODEL_CAVE_IO_CAVE_READER_H_
