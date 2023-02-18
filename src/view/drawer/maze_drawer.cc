#include "maze_drawer.h"

namespace s21 {

MazeDrawer::MazeDrawer(QWidget *parent) : QWidget(parent) {}

void MazeDrawer::DrawMaze(std::reference_wrapper<const maze::Maze> maze) {
  maze_ = maze;
  hasActualSolution_ = false;

  update();
}

void MazeDrawer::DrawMazeSolution(
    std::reference_wrapper<const maze::Solution> maze_solution) {
  maze_solution_ = maze_solution;
  hasActualSolution_ = true;

  update();
}

void MazeDrawer::paintEvent(QPaintEvent *event) {
  static_cast<void>(event);

  QPainter painter(this);

  painter.eraseRect(0, 0, 500, 500);

  QPen pen;
  pen.setWidth(2);

  painter.setPen(pen);

  painter.drawRect(1, 1, 498, 498);

  cell_w_ = (500 - 2 * (maze_.GetWidth() + 1)) / maze_.GetWidth();
  cell_h_ = (500 - 2 * (maze_.GetHeight() + 1)) / maze_.GetHeight();
  amount_of_wider_cells_ = 500 - (2 + cell_w_) * maze_.GetWidth();
  amount_of_higher_cells_ = 500 - (2 + cell_h_) * maze_.GetHeight();
  wall_w_ = 2 + cell_w_ + 2;
  wall_h_ = 2 + cell_h_ + 2;

  QBrush brush;
  brush.setStyle(Qt::SolidPattern);
  for (size_t i = 0; i < maze_.GetWidth(); i++) {
    for (size_t j = 0; j < maze_.GetHeight(); j++) {
      if (maze_.IsRightFree(s21::Coordinate(i, j)) == false) {
        DrawWallRight(&painter, s21::Coordinate(i, j), brush);
      }
      if (maze_.IsBottomFree(s21::Coordinate(i, j)) == false) {
        DrawWallBottom(&painter, s21::Coordinate(i, j), brush);
      }
    }
  }

  if (hasActualSolution_) {
    brush.setColor(Qt::green);
    s21::Coordinate cur = maze_solution_.front();
    for (auto it = std::next(maze_solution_.begin());
         it != maze_solution_.end(); it++) {
      s21::Coordinate next = *it;
      DrawSolutionLine(&painter, cur, next, brush);
      cur = next;
    }
  }
}

void MazeDrawer::DrawWallRight(QPainter *painter, Coordinate cell,
                               QBrush brush) {
  size_t wall_begin_w = (kWallWidth + cell_w_) * (cell.x + 1);
  if (cell.x < amount_of_wider_cells_) {
    wall_begin_w += cell.x + 1;
  } else {
    wall_begin_w += amount_of_wider_cells_;
  }
  size_t wall_begin_h = (kWallWidth + cell_h_) * cell.y;
  if (cell.y < amount_of_higher_cells_) {
    wall_begin_h += cell.y;
  } else {
    wall_begin_h += amount_of_higher_cells_;
  }
  size_t wall_len = wall_h_ + (cell.y < amount_of_higher_cells_);

  painter->fillRect(wall_begin_w, wall_begin_h, kWallWidth, wall_len, brush);
}

void MazeDrawer::DrawWallBottom(QPainter *painter, Coordinate cell,
                                QBrush brush) {
  size_t wall_begin_w = (kWallWidth + cell_w_) * cell.x;
  if (cell.x < amount_of_wider_cells_) {
    wall_begin_w += cell.x;
  } else {
    wall_begin_w += amount_of_wider_cells_;
  }
  size_t wall_begin_h = (kWallWidth + cell_h_) * (cell.y + 1);
  if (cell.y < amount_of_higher_cells_) {
    wall_begin_h += cell.y + 1;
  } else {
    wall_begin_h += amount_of_higher_cells_;
  }
  size_t wall_len = wall_w_ + (cell.x < amount_of_higher_cells_);

  painter->fillRect(wall_begin_w, wall_begin_h, wall_len, kWallWidth, brush);
}

void MazeDrawer::DrawSolutionLine(QPainter *painter, Coordinate cur,
                                  Coordinate next, QBrush brush) {
  if (cur.x > next.x || cur.y > next.y) {
    s21::Coordinate tmp = cur;
    cur = next;
    next = tmp;
  }
  size_t line_begin_w = (kWallWidth + cell_w_) * cur.x + cell_w_ / 2;
  if (cur.x < amount_of_wider_cells_) {
    line_begin_w += cur.x + 1;
  } else {
    line_begin_w += amount_of_wider_cells_;
  }
  size_t line_begin_h = (kWallWidth + cell_h_) * cur.y + cell_h_ / 2;
  if (cur.y < amount_of_higher_cells_) {
    line_begin_h += cur.y + 1;
  } else {
    line_begin_h += amount_of_higher_cells_;
  }

  if (cur.x == next.x) {
    size_t wall_len = wall_h_ + (cur.x < amount_of_higher_cells_);
    painter->fillRect(line_begin_w, line_begin_h, kWallWidth, wall_len, brush);
  } else {
    size_t wall_len = wall_w_ + (cur.y < amount_of_higher_cells_);
    painter->fillRect(line_begin_w, line_begin_h, wall_len, kWallWidth, brush);
  }
}

}  // namespace s21
