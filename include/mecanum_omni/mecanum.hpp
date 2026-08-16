#ifndef MECANUM_OMNI_MECANUM_HPP_
#define MECANUM_OMNI_MECANUM_HPP_

#include <array>
#include <cstddef>

namespace mecanum_omni
{

// =============================================================================
// Mecanum Wheel Inverse Kinematics Solver
// =============================================================================
//
// Given robot body velocities (vx, vy, omega), compute each wheel's angular velocity (rad/s)
//
// Coordinate frame:
//   +x  = forward
//   +y  = left
//   +omega = counter-clockwise (CCW) rotation
//
// Wheel numbering:
//   [0] = front-left  (FL)
//   [1] = front-right (FR)
//   [2] = rear-left   (RL)
//   [3] = rear-right  (RR)
//
// Kinematic model (4 mecanum wheels, 45 deg rollers):
// ---------------------------------------------------------------------------
// For each wheel i, the linear speed at the wheel contact point is:
//   vi = vx_component + vy_component + rotation_component
//
// Because mecanum rollers are at 45 deg, the wheel's effective direction
// is a combination of its own rotation axis and the roller angle.
//
//  Per-wheel equations:
//   w0 (FL) = (vx - vy - (L+W)*omega) / R
//   w1 (FR) = (vx + vy + (L+W)*omega) / R
//   w2 (RL) = (vx + vy - (L+W)*omega) / R
//   w3 (RR) = (vx - vy + (L+W)*omega) / R
//
//  Where:
//   R  = wheel_radius
//   L  = wheelbase / 2 (distance from CG to front/rear axle)
//   W  = track / 2 (distance from CG to left/right wheel)
//   CG = Center of Gravity (pusat massa robot, titik acuan gerak)
//
// Note on signs: if your robot behaves inverted in any axis, flip the corresponding sign
//
// Reference: https://robotsforroboticists.com/drive-kinematics/
// =============================================================================

class MecanumSolver
{
public:
  /// Compute wheel angular velocities [rad/s] from body velocities
  /// @param vx forward speed [m/s] (+ = forward)
  /// @param vy lateral speed [m/s] (+ = left)
  /// @param omega angular speed [rad/s] (+ = CCW)
  /// @return array of 4 wheel angular velocities {FL, FR, RL, RR} in [rad/s]
  std::array<double, 4> compute_wheel_speeds(double vx, double vy, double omega) const;
};

}

#endif
