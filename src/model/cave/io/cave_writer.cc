#include "cave_writer.h"

namespace s21 {

namespace cave {

void Writer::Write(const Cave& cave) {
  std::ofstream file(GenerateFilename(cave));
  if (file.is_open()) {
    file.clear();

    file << cave.width_ << ' ' << cave.height_ << std::endl;

    for (std::size_t i = 0; i < cave.height_; i++) {
      for (std::size_t j = 0; j < cave.width_ - 1; j++)
        file << cave.cave_[j][i] << ' ';
      file << cave.cave_[cave.width_ - 1][i] << std::endl;
    }

    file.close();
  }
}

std::string Writer::GenerateFilename(const Cave& cave) {
  std::stringstream ss;

  ss << "cave"
     << "_w" << cave.width_ << "_h" << cave.height_;

  auto time = std::time(nullptr);
  ss << "_" << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");

  ss << ".txt";

  return ss.str();
}

}  // namespace cave

}  // namespace s21
