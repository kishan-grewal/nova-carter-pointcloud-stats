#include "carter_bag_stats/bag_stats.hpp"

#include <chrono>                     // std::chrono::milliseconds
using namespace std::chrono_literals; // using namepsace -> convenient syntax
// e.g. stop including (std) or use suffix like ms (chrono)

MyPublisher::MyPublisher() : Node("my_publisher") {
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  timer_ = this->create_wall_timer(1000ms, [this]() { this->callback(); });
}

void MyPublisher::callback() {
  auto message = std_msgs::msg::String();
  message.data = "Hello World!";
  RCLCPP_INFO(this->get_logger(), message.data.c_str());
  publisher_->publish(message);
}