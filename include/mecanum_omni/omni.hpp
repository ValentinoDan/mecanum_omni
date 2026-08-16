#ifndef MECANUM_OMNI_OMNI_HPP_
#define MECANUM_OMNI_OMNI_HPP_
#include <array>
#include <cstddef>

namespace mecanum_omni
{

// =============================================================================
// Omni Wheel Inverse Kinematics Solver
// =============================================================================
//
// Given robot body velocities (vx, vy, omega), compute each wheel's angular velocity (rad/s)
//
// Coordinate frame:
//   +x  = forward
//   +y  = left
//   +omega = counter-clockwise (CCW) rotation
//
// Wheel numbering (4 wheels):
//   [0] = front-left  (alpha = 45 deg)
//   [1] = front-right (alpha = 135 deg)
//   [2] = rear-left   (alpha = 225 deg)
//   [3] = rear-right  (alpha = 315 deg)
//
// Kinematic model (omni wheels with 90 deg rollers):
// ---------------------------------------------------------------------------
// For each wheel i mounted at angle alpha_i and distance R from CG:
//
// The linear velocity at wheel i is the sum of:
//   1. Body translation projected onto the wheel's direction:
//      vi_trans = vx * cos(alpha_i) + vy * sin(alpha_i)
//
//   2. Rotation contribution from body spin:
//      vi_rot = omega * R
//
//   vi = vi_trans + vi_rot
//      = vx * cos(alpha_i) + vy * sin(alpha_i) + omega * R
//
// The wheel's angular velocity is then:
//   wi = vi / wheel_radius
//
// Per-wheel equations (cos(pi/4) = sqrt(2)/2):
//   alpha_0 = 45 deg: w0 = ( vx*sqrt(2)/2 + vy*sqrt(2)/2 + omega*R ) / r
//   alpha_1 = 135 deg: w1 = (-vx*sqrt(2)/2 + vy*sqrt(2)/2 + omega*R ) / r
//   alpha_2 = 225 deg: w2 = (-vx*sqrt(2)/2 - vy*sqrt(2)/2 + omega*R ) / r
//   alpha_3 = 315 deg: w3 = ( vx*sqrt(2)/2 - vy*sqrt(2)/2 + omega*R ) / r
//
// Where:
//   r = wheel_radius
//   R = distance from CG to wheel center (omni_wheel_distance)
//
// Note: Because omni wheels roll freely sideways, only the component along the wheel's driving direction matters
// =============================================================================

class OmniSolver
{
public:
  /// Compute wheel angular velocities [rad/s] from body velocities.
  /// @param vx forward speed [m/s] (+ = forward)
  /// @param vy lateral speed [m/s] (+ = left)
  /// @param omega angular speed [rad/s] (+ = Counter Clockwise)
  /// @return array of 4 wheel angular velocities {FL, FR, RL, RR} in [rad/s]
  std::array<double, 4> compute_wheel_speeds(double vx, double vy, double omega) const;
};

}

#endif
