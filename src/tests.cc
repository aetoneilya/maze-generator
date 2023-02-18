#include <gtest/gtest.h>

#include "model/model.h"

TEST(s21_cave_generator_tests, generation_test_1) {
  s21::Model m;
  std::size_t h = 4;
  std::size_t w = 4;
  m.SetCaveGenerator(s21::cave::GeneratorAlgorithm::kBasic);
  m.GenerateCave(w, h);
  s21::cave::Cave cave = m.GetCave();
  EXPECT_EQ(h, cave.GetHeight());
  EXPECT_EQ(w, cave.GetWidth());
}

TEST(s21_cave_generator_tests, generation_test_2) {
  s21::Model m;
  std::size_t h = 23;
  std::size_t w = 35;
  m.SetCaveGenerator(s21::cave::GeneratorAlgorithm::kBasic);
  m.GenerateCave(w, h);
  s21::cave::Cave cave = m.GetCave();
  EXPECT_EQ(h, cave.GetHeight());
  EXPECT_EQ(w, cave.GetWidth());
}

TEST(s21_cave_generator_tests, generation_test_3) {
  s21::Model m;
  std::size_t h = 50;
  std::size_t w = 50;
  m.SetCaveGenerator(s21::cave::GeneratorAlgorithm::kBasic);
  m.GenerateCave(w, h);
  s21::cave::Cave cave = m.GetCave();
  EXPECT_EQ(h, cave.GetHeight());
  EXPECT_EQ(w, cave.GetWidth());
}

TEST(s21_cave_generator_tests, step_test) {
  s21::Model m;
  std::size_t h = 50;
  std::size_t w = 50;
  m.SetCaveGenerator(s21::cave::GeneratorAlgorithm::kBasic);
  m.SetCaveBirthLimit(3);
  m.SetCaveDeathLimit(7);
  m.SetCaveInitialChance(45);

  m.GenerateCave(w, h);
  m.SetCaveSimulationStep(12);
}

TEST(s21_cave_generator_tests, throw_step_test) {
  s21::Model m;
  EXPECT_ANY_THROW(m.SetCaveBirthLimit(10));
  EXPECT_ANY_THROW(m.SetCaveDeathLimit(10));
}

TEST(s21_cave_base_generator_tests, step_test) {
  std::unique_ptr<s21::cave::generator::Basic> cg =
      std::make_unique<s21::cave::generator::Basic>();

  EXPECT_EQ(cg->GetBirthLimit(), 4);
  EXPECT_EQ(cg->GetDeathLimit(), 3);
  EXPECT_EQ(cg->GetInitialChance(), 45);
  EXPECT_EQ(cg->GetStep(), 0);
}

TEST(s21_maze_generator_tests, generation_test_1) {
  s21::Model m;
  std::size_t h = 4;
  std::size_t w = 4;
  m.SetMazeGenerator(s21::maze::GeneratorAlgorithm::kEller);
  m.GenerateMaze(w, h);
  s21::maze::Maze maze = m.GetMaze();
  EXPECT_EQ(h, maze.GetHeight());
  EXPECT_EQ(w, maze.GetWidth());
}
TEST(s21_maze_generator_tests, generation_test_2) {
  s21::Model m;
  std::size_t h = 24;
  std::size_t w = 43;
  m.SetMazeGenerator(s21::maze::GeneratorAlgorithm::kEller);
  m.GenerateMaze(w, h);
  s21::maze::Maze maze = m.GetMaze();
  EXPECT_EQ(h, maze.GetHeight());
  EXPECT_EQ(w, maze.GetWidth());
}

TEST(s21_maze_generator_tests, generation_test_3) {
  s21::Model m;
  std::size_t h = 50;
  std::size_t w = 50;
  m.SetMazeGenerator(s21::maze::GeneratorAlgorithm::kEller);
  m.GenerateMaze(w, h);
  s21::maze::Maze maze = m.GetMaze();
  EXPECT_EQ(h, maze.GetHeight());
  EXPECT_EQ(w, maze.GetWidth());
}

TEST(s21_maze_generator_tests, solvability_1) {
  s21::Model m;
  std::size_t h = 50;
  std::size_t w = 50;
  m.SetMazeGenerator(s21::maze::GeneratorAlgorithm::kEller);
  m.SetMazeSolver(s21::maze::SolverAlgorithm::kAStar);
  m.GenerateMaze(w, h);

  for (std::size_t x = 0; x < w; x++)
    for (std::size_t y = 0; y < w; y++) {
      m.SolveMaze({0, 0}, {x, y});
      s21::maze::Solution s = m.GetMazeSolution();
      EXPECT_TRUE(!s.empty());
    }
}

TEST(s21_cave_tests, invalid_construction) {
  EXPECT_ANY_THROW(s21::cave::Cave c(60, 60));
}

TEST(s21_cave_tests, valid_construction) {
  EXPECT_NO_THROW(s21::cave::Cave c(23, 22));
}

TEST(s21_cave_tests, operators) {
  s21::cave::Cave c_1(10, 10);
  s21::cave::Cave c_2(10, 10);
  c_2 = c_1;
  EXPECT_TRUE(c_1 == c_2);
}

TEST(s21_cave_tests, resize_throw) {
  s21::cave::Cave c;
  EXPECT_ANY_THROW(c.Resize(60, 60));
}

TEST(s21_cave_tests, valid_resize) {
  s21::cave::Cave c;
  c.Resize(6, 6);
  EXPECT_EQ(c.GetHeight(), 6);
  EXPECT_EQ(c.GetWidth(), 6);
}

TEST(s21_maze_tests, invalid_construction) {
  EXPECT_ANY_THROW(s21::maze::Maze m(60, 60));
}

TEST(s21_maze_tests, resize_throw) {
  s21::maze::Maze m;
  EXPECT_ANY_THROW(m.Resize(60, 60));
}

TEST(s21_maze_tests, valid_resize) {
  s21::maze::Maze m;
  m.Resize(6, 6);
  EXPECT_EQ(m.GetHeight(), 6);
  EXPECT_EQ(m.GetWidth(), 6);
}

TEST(s21_maze_tests, building_walls) {
  s21::maze::Maze m;
  m.BuildWallBottom({2, 2});
  m.BuildWallLeft({2, 2});
  m.BuildWallRight({2, 2});
  m.BuildWallTop({2, 2});

  EXPECT_FALSE(m.IsBottomFree({2, 2}));
  EXPECT_FALSE(m.IsLeftFree({2, 2}));
  EXPECT_FALSE(m.IsRightFree({2, 2}));
  EXPECT_FALSE(m.IsTopFree({2, 2}));

  m.DestroyWallBottom({2, 2});
  m.DestroyWallLeft({2, 2});
  m.DestroyWallRight({2, 2});
  m.DestroyWallTop({2, 2});

  EXPECT_TRUE(m.IsBottomFree({2, 2}));
  EXPECT_TRUE(m.IsLeftFree({2, 2}));
  EXPECT_TRUE(m.IsRightFree({2, 2}));
  EXPECT_TRUE(m.IsTopFree({2, 2}));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
