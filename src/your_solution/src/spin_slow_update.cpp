#include "spin_slow_update.h"
using std::placeholders::_1;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

SlowSolution::SlowSolution() : Node("slowsolution")
{
  mp_subscription_ = this->create_subscription<ArrayMsg>(
      "measuredpos", 10, std::bind(&SlowSolution::topic_callback, this, _1));

  publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);
}
void SlowSolution::topic_callback(const ArrayMsg::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%f' , '%f", msg->data[0], msg->data[1]);
  publisher_->publish(*msg);
}
rclcpp::Subscription<ArrayMsg>::SharedPtr mp_subscription_;
rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_;

// your code here