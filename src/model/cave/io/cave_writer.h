#ifndef SRC_MODEL_CAVE_IO_CAVE_WRITER_H_
#define SRC_MODEL_CAVE_IO_CAVE_WRITER_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../cave.h"

namespace s21 {

namespace cave {

class Writer {
 public:
  Writer() = delete;

  static void Write(const Cave& cave);

 private:
  static std::string GenerateFilename(const Cave& cave);
};

}  // namespace cave

}  // namespace s21

#endif  // SRC_MODEL_CAVE_IO_CAVE_WRITER_H_
