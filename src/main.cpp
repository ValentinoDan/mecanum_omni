#include <chrono>
#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "mecanum_omni/mecanum.hpp"
#include "mecanum_omni/omni.hpp"

using namespace std::chrono_literals;

namespace mecanum_omni
{

class MecanumOmniNode : public rclcpp::Node
{
public:
  explicit MecanumOmniNode(const rclcpp::NodeOptions & options)
  : Node("mecanum_omni_node", options),
    solver_type_(declare_parameter<std::string>("solver_type", "mecanum"))
  {
    RCLCPP_INFO(get_logger(), "Solver type: %s", solver_type_.c_str());

    cmd_vel_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        this->on_cmd_vel(msg);
      });

    wheel_speeds_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>("wheel_speeds", 10);

    RCLCPP_INFO(get_logger(), "Node started. Listening on /cmd_vel, publishing on /wheel_speeds");
  }

private:
  void on_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    const double vx = msg->linear.x;
    const double vy = msg->linear.y;
    const double omega = msg->angular.z;

    std::array<double, 4> wheel_speeds{};

    if (solver_type_ == "mecanum") {
      wheel_speeds = mecanum_solver_.compute_wheel_speeds(vx, vy, omega);
    } else if (solver_type_ == "omni") {
      wheel_speeds = omni_solver_.compute_wheel_speeds(vx, vy, omega);
    } else {
      RCLCPP_ERROR(
        get_logger(), "Unknown solver_type: %s. Use 'mecanum' or 'omni'.",
        solver_type_.c_str());
      return;
    }

    auto out_msg = std_msgs::msg::Float64MultiArray();
    out_msg.data = {wheel_speeds[0], wheel_speeds[1], wheel_speeds[2], wheel_speeds[3]};
    wheel_speeds_pub_->publish(out_msg);

    RCLCPP_INFO(
      get_logger(),
      "cmd_vel=(%.3f, %.3f, %.3f) -> wheel_speeds=(FL=%.3f, FR=%.3f, RL=%.3f, RR=%.3f)",
      vx, vy, omega,
      wheel_speeds[0], wheel_speeds[1], wheel_speeds[2], wheel_speeds[3]);
  }

  std::string solver_type_;
  MecanumSolver mecanum_solver_;
  OmniSolver omni_solver_;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr wheel_speeds_pub_;
};

}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  auto node = std::make_shared<mecanum_omni::MecanumOmniNode>(options);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
