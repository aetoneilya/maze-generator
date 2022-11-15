#ifndef SRC_VIEW_DRAWER_MAZE_DRAWER_H_
#define SRC_VIEW_DRAWER_MAZE_DRAWER_H_

#include <QPainter>
#include <QWidget>

#include "../../controller/controller.h"

namespace s21 {

class MazeDrawer : public QWidget {
  Q_OBJECT

 public:
  explicit MazeDrawer(QWidget *parent = nullptr);

  void DrawMaze(std::reference_wrapper<const maze::Maze> maze);
  void DrawMazeSolution(
      std::reference_wrapper<const maze::Solution> maze_solution);

 protected:
  void paintEvent(QPaintEvent *event) override;

  void DrawWallRight(QPainter *painter, s21::Coordinate cell, QBrush brush);
  void DrawWallBottom(QPainter *painter, s21::Coordinate cell, QBrush brush);
  void DrawSolutionLine(QPainter *painter, s21::Coordinate cur,
                        s21::Coordinate next, QBrush brush);

 private:
  static const std::size_t kWallWidth = 2;
  size_t cell_w_ = 0;
  size_t cell_h_ = 0;
  size_t amount_of_wider_cells_ = 0;
  size_t amount_of_higher_cells_ = 0;
  size_t wall_w_ = 0;
  size_t wall_h_ = 0;

  maze::Maze maze_ = maze::Maze(3, 2);

  bool hasActualSolution_ = false;
  maze::Solution maze_solution_;
};

}  // namespace s21

#endif  // SRC_VIEW_DRAWER_MAZE_DRAWER_H_
