#include "mecanum_omni/omni.hpp"
#include "mecanum_omni/robot_geometry.hpp"

#include <array>
#include <cmath>

namespace mecanum_omni
{

std::array<double, 4> OmniSolver::compute_wheel_speeds(double vx, double vy, double omega) const
{
  // TODO: Implement the omni inverse kinematics formula
  // HINT: Look at the per-wheel equations in omni.hpp
  // Use the constants from robot_geometry.hpp:
  //   wheel_radius, omni_wheel_distance, omni_alpha[]
  // Return {w0, w1, w2, w3} = {FL, FR, RL, RR}
  //
  // Example for FL (wheel 0, alpha = 45 deg):
  //   w0 = (vx * cos(alpha_0) + vy * sin(alpha_0) + omega * omni_wheel_distance) / wheel_radius
  //
  // use std::cos and std::sin from <cmath> for the trigonometric functions
  // Make sure to fill in all 4 wheels

  std::array<double, 4> wheel_speeds = {0.0, 0.0, 0.0, 0.0};
  return wheel_speeds;
}

}
