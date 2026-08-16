#include "mecanum_omni/mecanum.hpp"
#include "mecanum_omni/robot_geometry.hpp"

#include <array>
#include <cmath>

namespace mecanum_omni
{

std::array<double, 4> MecanumSolver::compute_wheel_speeds(
  double vx, double vy, double omega) const
{
  // TODO: Implement the mecanum inverse kinematics formula
  // HINT: Look at the matrix and per-wheel equations in mecanum.hpp
  // Use the constants from robot_geometry.hpp:
  //   wheel_radius, L, W
  // Return {w0, w1, w2, w3} = {FL, FR, RL, RR}
  //
  // Example for FL (wheel 0):
  //   w0 = (vx - vy - (L + W) * omega) / wheel_radius
  //
  // Make sure to fill in all 4 wheels

  std::array<double, 4> wheel_speeds = {0.0, 0.0, 0.0, 0.0};
  return wheel_speeds;
}

}
