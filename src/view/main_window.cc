#include "main_window.h"

#include "ui_main_window.h"

namespace s21 {

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);

  auto app_config = controller_->GetCAppConfig();

  controller_->SetMazeGenerator(app_config.GetMazeGeneratorAlgorithm());
  controller_->SetMazeSolver(app_config.GetMazeSolverAlgorithm());

  ui->maze_width_box->setValue(app_config.GetMazeWidth());
  ui->maze_height_box->setValue(app_config.GetMazeHeight());

  ui->start_point_w_box->setValue(app_config.GetMazeSolverStart().x + 1);
  ui->start_point_h_box->setValue(app_config.GetMazeSolverStart().y + 1);
  ui->end_point_w_box->setValue(app_config.GetMazeSolverEnd().x + 1);
  ui->end_point_h_box->setValue(app_config.GetMazeSolverEnd().y + 1);

  controller_->GenerateMaze(app_config.GetMazeWidth(),
                            app_config.GetMazeHeight());
  ui->Maze->DrawMaze(controller_->GetMaze());

  controller_->SetCaveGenerator(app_config.GetCaveGeneratorAlgorithm());

  controller_->SetCaveInitialChance(app_config.GetCaveInitialChance());
  controller_->SetCaveBirthLimit(app_config.GetCaveBirthLimit());
  controller_->SetCaveDeathLimit(app_config.GetCaveDeathLimit());

  ui->cave_w_box->setValue(app_config.GetCaveWidth());
  ui->cave_h_box->setValue(app_config.GetCaveHeight());

  ui->init_chance_box->setValue(app_config.GetCaveInitialChance());
  ui->spinBox->setValue(app_config.GetCaveBirthLimit());
  ui->death_limit_box->setValue(app_config.GetCaveDeathLimit());

  ui->auto_step_check_box->setChecked(app_config.GetAutoStepEnabled());

  GenerateCompleteCave();
  ui->Cave->DrawCave(controller_->GetCave());

  connect(timer_.get(), &QTimer::timeout, this, &MainWindow::make_cave_step);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_maze_width_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeWidth(static_cast<std::size_t>(value));

  ui->start_point_w_box->setMaximum(value);
  ui->end_point_w_box->setMaximum(value);
}

void MainWindow::on_maze_height_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeHeight(static_cast<std::size_t>(value));

  ui->start_point_h_box->setMaximum(value);
  ui->end_point_h_box->setMaximum(value);
}

void MainWindow::on_start_point_w_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeSolverStart(
      {static_cast<std::size_t>(value - 1),
       controller_->GetCAppConfig().GetMazeSolverStart().y});
}

void MainWindow::on_end_point_w_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeSolverEnd(
      {static_cast<std::size_t>(value - 1),
       controller_->GetCAppConfig().GetMazeSolverEnd().y});
}

void MainWindow::on_start_point_h_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeSolverStart(
      {controller_->GetCAppConfig().GetMazeSolverStart().x,
       static_cast<std::size_t>(value - 1)});
}

void MainWindow::on_end_point_h_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetMazeSolverEnd(
      {controller_->GetCAppConfig().GetMazeSolverEnd().x,
       static_cast<std::size_t>(value - 1)});
}

void MainWindow::on_generate_maze_button_clicked() {
  controller_->GenerateMaze(controller_->GetCAppConfig().GetMazeWidth(),
                            controller_->GetCAppConfig().GetMazeHeight());
  ui->Maze->DrawMaze(controller_->GetMaze());
}

void MainWindow::on_solve_maze_button_clicked() {
  controller_->SolveMaze(controller_->GetCAppConfig().GetMazeSolverStart(),
                         controller_->GetCAppConfig().GetMazeSolverEnd());
  ui->Maze->DrawMazeSolution(controller_->GetMazeSolution());
}

void MainWindow::on_save_maze_button_clicked() { controller_->WriteMaze(); }

void MainWindow::on_load_maze_button_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                                                  QDir::currentPath());
  controller_->ReadMaze(
      filename.toStdString(), [this](const std::string &msg) -> void {
        ShowMessage(QMessageBox::Icon::Critical,
                    QGuiApplication::applicationDisplayName(),
                    tr("Не удалось загрузить лабиринт: %1").arg(msg.c_str()));
      });
  ui->Maze->DrawMaze(controller_->GetMaze());
}

void MainWindow::on_generate_cave_button_clicked() {
  if (timer_ && timer_->isActive()) timer_->stop();

  controller_->SetCaveInitialChance(
      controller_->GetCAppConfig().GetCaveInitialChance());
  controller_->SetCaveBirthLimit(
      controller_->GetCAppConfig().GetCaveBirthLimit());
  controller_->SetCaveDeathLimit(
      controller_->GetCAppConfig().GetCaveDeathLimit());

  GenerateCompleteCave();

  ui->Cave->DrawCave(controller_->GetCave());
}

void MainWindow::on_init_chance_box_valueChanged(double value) {
  controller_->GetAppConfig()->SetCaveInitialChance(value);
}

void MainWindow::on_spinBox_valueChanged(int value) {
  controller_->GetAppConfig()->SetCaveBirthLimit(value);
}

void MainWindow::on_death_limit_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetCaveDeathLimit(value);
}

void MainWindow::on_cave_w_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetCaveWidth(value);
}

void MainWindow::on_cave_h_box_valueChanged(int value) {
  controller_->GetAppConfig()->SetCaveHeight(value);
}

void MainWindow::on_begin_generation_button_clicked() {
  if (timer_ && timer_->isActive()) timer_->stop();

  controller_->GenerateCave(controller_->GetCAppConfig().GetCaveWidth(),
                            controller_->GetCAppConfig().GetCaveHeight());

  if (controller_->GetCAppConfig().GetAutoStepEnabled()) {
    timer_->start(ui->step_interval_box->value());
  } else {
    ui->Cave->DrawCave(controller_->GetCave());
  }
}

void MainWindow::on_next_step_button_clicked() {
  if (timer_ && timer_->isActive()) timer_->stop();

  make_cave_step();
}

void MainWindow::on_load_cave_button_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                                                  QDir::currentPath());
  controller_->ReadCave(
      filename.toStdString(), [this](const std::string &msg) -> void {
        ShowMessage(QMessageBox::Icon::Critical,
                    QGuiApplication::applicationDisplayName(),
                    tr("Не удалось загрузить пещеру: %1").arg(msg.c_str()));
      });
  ui->Cave->DrawCave(controller_->GetCave());
}

void MainWindow::on_save_cave_button_clicked() { controller_->WriteCave(); }

void MainWindow::ShowMessage(QMessageBox::Icon type, const QString &title,
                             const QString &message) {
  QMessageBox message_box(
      type, title, message, QMessageBox::StandardButton::Ok, this,
      Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
  message_box.setModal(true);
  message_box.exec();
}

void MainWindow::on_auto_step_check_box_stateChanged(int arg1) {
  controller_->GetAppConfig()->SetAutoStepEnabled(static_cast<bool>(arg1));
}

void MainWindow::make_cave_step() {
  controller_->SetCaveSimulationStep(1);
  ui->Cave->DrawCave(controller_->GetCave());
}

void MainWindow::GenerateCompleteCave() {
  controller_->GenerateCave(controller_->GetCAppConfig().GetCaveWidth(),
                            controller_->GetCAppConfig().GetCaveHeight());

  cave::Cave cave_ = controller_->GetCave();
  controller_->SetCaveSimulationStep(1);
  cave::Cave new_cave_ = controller_->GetCave();
  while (!(cave_ == new_cave_)) {
    controller_->SetCaveSimulationStep(1);
    cave_ = new_cave_;
    new_cave_ = controller_->GetCave();
  }
}

}  // namespace s21
