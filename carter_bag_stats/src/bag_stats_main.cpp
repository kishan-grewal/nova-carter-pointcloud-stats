#include "carter_bag_stats/bag_stats.hpp"

#include <memory>

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  // rclcpp::executors::MultiThreadedExecutor
  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 2);
  executor.add_node(std::make_shared<BagStats>());
  executor.spin();
  rclcpp::shutdown();
  return 0;
}