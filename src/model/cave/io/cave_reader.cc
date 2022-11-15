#include "cave_reader.h"

namespace s21 {

namespace cave {

Cave Reader::Read(const std::string& filename) {
  Cave cave;

  std::ifstream file(filename);
  if (file.is_open()) {
    file >> cave.width_ >> cave.height_;

    if (cave.width_ >= Cave::kMinWidth && cave.width_ <= Cave::kMaxWidth &&
        cave.height_ >= Cave::kMinHeight && cave.height_ <= Cave::kMaxHeight) {
      for (std::size_t i = 0; i < cave.height_; i++) {
        for (std::size_t j = 0; j < cave.width_; j++) file >> cave.cave_[i][j];
      }
    } else {
      throw std::runtime_error("ошибка чтения");
    }

    file.close();
  } else {
    throw std::runtime_error("файл не найден");
  }

  return cave;
}

}  // namespace cave

}  // namespace s21
