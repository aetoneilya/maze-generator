#include "cave.h"

namespace s21 {

namespace cave {

Cave::Cave() : width_(kMaxWidth), height_(kMaxHeight) {}

Cave::Cave(std::size_t width, std::size_t height) {
  if (width < kMinWidth || width > kMaxWidth || height < kMinHeight ||
      height > kMaxHeight) {
    throw std::invalid_argument("Wrong size of cave");
  }

  width_ = width;
  height_ = height;
}

Cave::Cave(const Cave& other)
    : width_(other.width_), height_(other.height_), cave_(other.cave_) {}

Cave::Cave(Cave&& other) { Swap(&other); }

bool Cave::operator==(const Cave& other) { return cave_ == other.cave_; }

Cave& Cave::operator=(const Cave& other) {
  if (this != &other) {
    Cave(other).Swap(this);
  }
  return *this;
}

Cave& Cave::operator=(Cave&& other) {
  if (this != &other) {
    Cave(std::move(other)).Swap(this);
  }
  return *this;
}

void Cave::Swap(Cave* other) {
  std::swap(width_, other->width_);
  std::swap(height_, other->height_);

  std::swap(cave_, other->cave_);
}

std::size_t Cave::GetWidth() const { return width_; }

std::size_t Cave::GetHeight() const { return height_; }

void Cave::Resize(std::size_t width, std::size_t height) {
  if (width < kMinWidth || width > kMaxWidth || height < kMinHeight ||
      height > kMaxHeight) {
    throw std::invalid_argument("Wrong size of cave");
  }

  width_ = width;
  height_ = height;
}

}  // namespace cave

}  // namespace s21
