#include <gtest/gtest.h>

#include "mecanum_omni/omni.hpp"
#include "mecanum_omni/robot_geometry.hpp"

#include <cmath>

using mecanum_omni::OmniSolver;
using mecanum_omni::wheel_radius;

TEST(OmniSolver, TestForward)
{
  OmniSolver solver;
  auto wheels = solver.compute_wheel_speeds(1.0, 0.0, 0.0);

  // Expected for FL and RR (alpha = 45 and 315):
  //   cos(45) = sqrt(2)/2, sin(45) = sqrt(2)/2
  // For FR and RL (alpha = 135 and 225):
  //   cos(135) = -sqrt(2)/2, sin(135) = sqrt(2)/2
  //
  // With vy=0 and omega=0:
  //   w0 = vx * cos(45) / r = (1.0 * sqrt(2)/2) / 0.05 = 10 * sqrt(2) = 14.1421
  //   w1 = vx * cos(135) / r = (1.0 * -sqrt(2)/2) / 0.05 = -14.1421
  //   w2 = vx * cos(225) / r = -14.1421
  //   w3 = vx * cos(315) / r = 14.1421

  const double expected_pos = (1.0 * std::sqrt(2.0) / 2.0) / wheel_radius;
  const double expected_neg = -expected_pos;

  EXPECT_NEAR(wheels[0], expected_pos, 1e-6); // FL
  EXPECT_NEAR(wheels[1], expected_neg, 1e-6); // FR
  EXPECT_NEAR(wheels[2], expected_neg, 1e-6); // RL
  EXPECT_NEAR(wheels[3], expected_pos, 1e-6); // RR
}
