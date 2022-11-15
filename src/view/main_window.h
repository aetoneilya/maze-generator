#ifndef SRC_VIEW_MAIN_WINDOW_H_
#define SRC_VIEW_MAIN_WINDOW_H_

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QTimer>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_maze_width_box_valueChanged(int value);
  void on_maze_height_box_valueChanged(int value);

  void on_start_point_w_box_valueChanged(int value);
  void on_end_point_w_box_valueChanged(int value);
  void on_start_point_h_box_valueChanged(int value);
  void on_end_point_h_box_valueChanged(int value);

  void on_generate_maze_button_clicked();
  void on_solve_maze_button_clicked();

  void on_save_maze_button_clicked();
  void on_load_maze_button_clicked();

  void on_generate_cave_button_clicked();

  void on_init_chance_box_valueChanged(double value);
  void on_spinBox_valueChanged(int value);
  void on_death_limit_box_valueChanged(int value);

  void on_cave_w_box_valueChanged(int value);
  void on_cave_h_box_valueChanged(int value);

  void on_next_step_button_clicked();
  void on_begin_generation_button_clicked();

  void on_load_cave_button_clicked();
  void on_save_cave_button_clicked();

  void on_auto_step_check_box_stateChanged(int arg1);

  void make_cave_step();

 private:
  void ShowMessage(QMessageBox::Icon type, const QString &title,
                   const QString &message);
  void GenerateCompleteCave();

  Ui::MainWindow *ui;
  Controller *controller_;

  std::unique_ptr<QTimer> timer_ = std::make_unique<QTimer>(this);
};

}  // namespace s21

#endif  // SRC_VIEW_MAIN_WINDOW_H_
