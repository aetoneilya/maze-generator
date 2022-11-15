#ifndef SRC_MODEL_CAVE_CAVE_H_
#define SRC_MODEL_CAVE_CAVE_H_

#include <array>
#include <stdexcept>

namespace s21 {

class CaveDrawer;

namespace cave {

namespace generator {

class Basic;

}

class Cave {
 public:
  static const std::size_t kMinWidth = 2;
  static const std::size_t kMaxWidth = 50;
  static const std::size_t kMinHeight = 2;
  static const std::size_t kMaxHeight = 50;

  Cave();
  Cave(std::size_t width, std::size_t height);
  Cave(const Cave& other);
  Cave(Cave&& other);

  bool operator==(const Cave& other);
  Cave& operator=(const Cave& other);
  Cave& operator=(Cave&& other);

  void Swap(Cave* other);

  std::size_t GetWidth() const;
  std::size_t GetHeight() const;

  void Resize(std::size_t width, std::size_t height);

 private:
  using InternalCave = std::array<std::array<bool, kMaxHeight>, kMaxWidth>;

  friend class generator::Basic;
  friend class Reader;
  friend class Writer;
  friend class ::s21::CaveDrawer;

  std::size_t width_;
  std::size_t height_;

  InternalCave cave_;
};

}  // namespace cave

}  // namespace s21

#endif  // SRC_MODEL_CAVE_CAVE_H_
