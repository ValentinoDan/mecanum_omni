#ifndef MECANUM_OMNI_ROBOT_GEOMETRY_HPP_
#define MECANUM_OMNI_ROBOT_GEOMETRY_HPP_
#include <cmath>

namespace mecanum_omni
{

constexpr double wheel_radius = 0.05; // radius of each wheel (m)
constexpr double wheelbase = 0.50; // distance between front and rear wheels (m)
constexpr double track = 0.40; // distance between left and right wheels (m)

// Mecanum wheels with 45 degree rollers
constexpr double mecanum_roller_angle = M_PI / 4.0;  // 45 [rad]

// CG = Center of Gravity (pusat massa robot). Ini adalah titik acuan (origin)
constexpr double L = wheelbase / 2.0; // distance from CG to front/rear axle
constexpr double W = track / 2.0; // distance from CG to left/right wheel

constexpr double omni_wheel_distance = std::sqrt(L * L + W * W);

constexpr double omni_alpha[4] = {
  M_PI / 4.0, // front-left  (45 deg)
  3.0 * M_PI / 4.0, // front-right (135 deg)
  5.0 * M_PI / 4.0, // rear-left   (225 deg)
  7.0 * M_PI / 4.0 // rear-right  (315 deg)
};

}

#endif
