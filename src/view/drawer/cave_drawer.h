#ifndef SRC_VIEW_DRAWER_CAVE_DRAWER_H_
#define SRC_VIEW_DRAWER_CAVE_DRAWER_H_

#include <QPainter>
#include <QWidget>

#include "../../controller/controller.h"

namespace s21 {

class CaveDrawer : public QWidget {
 public:
  explicit CaveDrawer(QWidget *parent = nullptr);

  void DrawCave(const cave::Cave &cave);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  cave::Cave cave_;
};

}  // namespace s21

#endif  // SRC_VIEW_DRAWER_CAVE_DRAWER_H_
