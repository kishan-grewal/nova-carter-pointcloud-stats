#pragma once

#include <memory> // shared ptr
#include <string> // std::string and to_string

#include "rclcpp/rclcpp.hpp" // node, init, spin, shutdown, RCLCPP_INFO (#define)
#include "std_msgs/msg/string.hpp" // std_msgs::msg::String

class MyPublisher : public rclcpp::Node {
public:
  MyPublisher();

private:
  void callback();
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};
