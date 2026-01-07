#include "carter_bag_stats/bag_stats.hpp"

#include <chrono>                     // std::chrono::milliseconds
// using namespace std::chrono_literals; // using namepsace -> convenient syntax
// e.g. stop including (std) or use suffix like ms (chrono)

#include <cmath> 

BagStats::BagStats() : Node("bag_stats") {
  rclcpp::QoS odom_qos(10);
  odom_qos.reliability(rclcpp::ReliabilityPolicy::Reliable);

  rclcpp::QoS lidar_qos(10);
  lidar_qos.reliability(rclcpp::ReliabilityPolicy::BestEffort);

  chassis_odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "/chassis/odom", odom_qos,
      [this](const nav_msgs::msg::Odometry::SharedPtr msg) {  
        this->chassis_odom_callback_(msg);
      });

  front_lidar_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/front_3d_lidar/lidar_points", lidar_qos,
      [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        this->front_lidar_callback_(msg);
      });
  
  stats_period_ms_ = this->declare_parameter("stats_period", stats_period_ms_);
  stats_pub_ = this->create_publisher<std_msgs::msg::String>("/bag_stats", 10);
  stats_timer_ =
      this->create_wall_timer(std::chrono::milliseconds(stats_period_ms_), [this]() { this->stats_callback(); });
}

void BagStats::chassis_odom_callback_(const nav_msgs::msg::Odometry::SharedPtr msg) {
  // const auto &stamp = msg->header.stamp;
  const auto &position = msg->pose.pose.position;
  // const auto &orientation = msg->pose.pose.orientation;
  const auto &linear = msg->twist.twist.linear;
  const auto &angular = msg->twist.twist.angular;

  double x = position.x;
  double y = position.y;
  double vx = linear.x;
  double vy = linear.y;
  double wx = angular.x;
  double wy = angular.y;

  {
    std::lock_guard<std::mutex> lock(stats_mutex_);

    odom_count_++;

    if (odom_count_ > 1) {
      double dx = x - last_x_;
      double dy = y - last_y_;
      total_distance_ += std::sqrt(dx * dx + dy * dy);
    }
    last_x_ = x;
    last_y_ = y;

    total_speed_ += std::sqrt(vx * vx + vy * vy);
    average_speed_ = total_speed_ / odom_count_;

    if (wx * wx + wy * wy > max_turn_ * max_turn_) {
      max_turn_ = std::sqrt(wx * wx + wy * wy);
    }
  }
}

void BagStats::front_lidar_callback_(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
  // const auto &stamp = msg->header.stamp;
  // const auto &data = msg->data;
  std::lock_guard<std::mutex> lock(stats_mutex_);

  points_count_++;

  size_t num_points = msg->width * msg->height;

  total_points_ += num_points;
  average_points_ = static_cast<double>(total_points_) / points_count_;

  if (num_points > max_points_) {
    max_points_ = num_points;
  }
}

void BagStats::stats_callback() const {
  std::lock_guard<std::mutex> lock(stats_mutex_);
  auto message = std_msgs::msg::String();
  message.data = 
    "Odom: " + std::to_string(odom_count_) + 
    ", Distance: " + std::to_string(total_distance_) + "m" +
    ", Avg Speed: " + std::to_string(average_speed_) + "m/s" +
    ", Max Turn: " + std::to_string(max_turn_) + "rad/s" +
    " | Points: " + std::to_string(points_count_) +
    ", Avg Points: " + std::to_string(average_points_) +
    ", Max Points: " + std::to_string(max_points_);
  
  RCLCPP_INFO(this->get_logger(), "%s", message.data.c_str());
  stats_pub_->publish(message);
}