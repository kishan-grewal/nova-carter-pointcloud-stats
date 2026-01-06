#include <chrono>                     // std::chrono::milliseconds
using namespace std::chrono_literals; // using namepsace -> convenient syntax
// e.g. stop including (std) or use suffix like ms (chrono)

#include <memory> // shared ptr
#include <string> // std::string and to_string

#include "carter_bag_stats/bag_stats.hpp"
#include "rclcpp/rclcpp.hpp" // node, init, spin, shutdown, RCLCPP_INFO (#define)
#include "std_msgs/msg/string.hpp" // std_msgs::msg::String

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}