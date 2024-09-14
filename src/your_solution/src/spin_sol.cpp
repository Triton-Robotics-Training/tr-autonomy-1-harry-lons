#include "spin_sol.h"
using std::placeholders::_1;
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

SpinSolution::SpinSolution() : Node("spinsolution"), curr_pos(2,0.0f), curr_vel(2,0.0f) {
  // initialize measuredpos subscription
  mp_subscription_ = this->create_subscription<ArrayMsg>(
      "measuredpos", 10, std::bind(&SpinSolution::pos_callback, this, _1));
  // initialize measuredvel subscription
  mv_subscription_ = this->create_subscription<ArrayMsg>(
      "measuredvel", 10, std::bind(&SpinSolution::vel_callback, this, _1));
  // initialize publisher to predictedpos
  publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);

  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(0),
    std::bind(&SpinSolution::update_pos, this));
}

void SpinSolution::update_pos(){
  ArrayMsg::SharedPtr msg = std::make_shared<ArrayMsg>();
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = now - last_msg;
  double dt = elapsed.count();
  msg->data.resize(2);
  msg->data[0] = curr_pos[0] + ( dt * curr_vel[0] );
  msg->data[1] = curr_pos[1] + ( dt * curr_vel[1] );
  publisher_->publish(*msg);
}

void SpinSolution::pos_callback(const ArrayMsg::SharedPtr msg) {
  last_msg = std::chrono::system_clock::now();
  this->curr_pos = {msg->data[0], msg->data[1]};
  publisher_->publish(*msg);
}

void SpinSolution::vel_callback(const ArrayMsg::SharedPtr msg) {
  this->curr_vel = {msg->data[0], msg->data[1]};
}