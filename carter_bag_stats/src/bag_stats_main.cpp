#include "carter_bag_stats/bag_stats.hpp"

#include <memory>

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  // rclcpp::executors::MultiThreadedExecutor
  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 2);
  // always keep node in a variable don't create it as an r-value in executor add node line
  // otherwise its lifetime ends before the executor runs
  auto node = std::make_shared<BagStats>();
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}