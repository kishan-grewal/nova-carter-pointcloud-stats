#include "carter_bag_stats/bag_stats.hpp"

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}