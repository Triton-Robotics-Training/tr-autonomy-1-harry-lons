#include "spin_slow_update.h"
using std::placeholders::_1;

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

  SlowSolution::SlowSolution() : Node("slowsolution") {
    subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "measuredpos", 10, std::bind(&SlowSolution::topic_callback, this, _1));
    // your code here
  }
  void SlowSolution::topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%f' , '%f", msg->data[0], msg->data[1]);
    }
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;

  // your code here