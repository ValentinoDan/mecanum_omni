#include <gtest/gtest.h>

#include "mecanum_omni/mecanum.hpp"
#include "mecanum_omni/robot_geometry.hpp"

using mecanum_omni::MecanumSolver;
using mecanum_omni::wheel_radius;

TEST(MecanumSolver, TestForward)
{
  MecanumSolver solver;
  auto wheels = solver.compute_wheel_speeds(1.0, 0.0, 0.0);

  // Expected: all wheels same speed = vx / wheel_radius
  const double expected = 1.0 / wheel_radius;

  EXPECT_NEAR(wheels[0], expected, 1e-6); // FL
  EXPECT_NEAR(wheels[1], expected, 1e-6); // FR
  EXPECT_NEAR(wheels[2], expected, 1e-6); // RL
  EXPECT_NEAR(wheels[3], expected, 1e-6); // RR
}
