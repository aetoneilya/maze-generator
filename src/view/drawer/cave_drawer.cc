#include "cave_drawer.h"

namespace s21 {

CaveDrawer::CaveDrawer(QWidget *parent) : QWidget(parent) {}

void CaveDrawer::DrawCave(const cave::Cave &cave) {
  cave_ = cave;

  update();
}

void CaveDrawer::paintEvent(QPaintEvent *event) {
  static_cast<void>(event);
  QPainter painter(this);

  painter.eraseRect(0, 0, 500, 500);

  QBrush brush;
  brush.setStyle(Qt::SolidPattern);

  std::size_t cell_w = 500 / cave_.width_;
  std::size_t cell_h = 500 / cave_.height_;
  std::size_t leftover_w = 500 - cell_w * cave_.width_;
  std::size_t leftover_h = 500 - cell_h * cave_.height_;

  for (size_t i = 0; i < cave_.width_; i++) {
    size_t extra_w = i < leftover_w ? i : leftover_w;
    for (size_t j = 0; j < cave_.height_; j++) {
      if (cave_.cave_.at(i).at(j) == true) {
        size_t extra_h = j < leftover_h ? j : leftover_h;
        painter.fillRect(cell_w * i + extra_w, cell_h * j + extra_h,
                         cell_w + (i < leftover_w), cell_h + (j < leftover_h),
                         brush);
      }
    }
  }
}

}  // namespace s21
