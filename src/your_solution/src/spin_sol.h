#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SpinSolution : public rclcpp::Node
{
public:
    SpinSolution();
private:
    rclcpp::Subscription<ArrayMsg>::SharedPtr mp_subscription_;
    rclcpp::Subscription<ArrayMsg>::SharedPtr mv_subscription_;
    rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::chrono::time_point<std::chrono::system_clock> last_msg;
    std::vector<double> curr_pos;
    std::vector<double> curr_vel;

    void update_pos();
    void pos_callback(const ArrayMsg::SharedPtr msg) ;
    void vel_callback(const ArrayMsg::SharedPtr msg) ;
};

#endif // YOUR_SOLUTION_SRC_SPIN_SOL_H_
