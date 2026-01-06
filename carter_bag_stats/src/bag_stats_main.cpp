#include "carter_bag_stats/bag_stats.hpp"

#include <memory>

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BagStats>());
  rclcpp::shutdown();
  return 0;
}