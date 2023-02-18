#ifndef SRC_MODEL_UTILS_H_
#define SRC_MODEL_UTILS_H_

#include <utility>

namespace s21 {

template <typename Key, typename Value>
class Pair {
 public:
  Pair(Key key, Value value) : x(key), y(value) {}

  Key x;
  Value y;
};

using Coordinate = Pair<std::size_t, std::size_t>;

}  // namespace s21

#endif  // SRC_MODEL_UTILS_H_
