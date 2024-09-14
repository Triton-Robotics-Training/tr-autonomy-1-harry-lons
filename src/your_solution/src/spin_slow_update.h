#ifndef YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_
#define YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SlowSolution : public rclcpp::Node
{
public:
  SlowSolution();

private:
  rclcpp::Subscription<ArrayMsg>::SharedPtr mp_subscription_;
  rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_;

  void topic_callback(const ArrayMsg::SharedPtr msg) const;
};

#endif // YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_
