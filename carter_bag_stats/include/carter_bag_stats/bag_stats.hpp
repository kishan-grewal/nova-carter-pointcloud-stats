#pragma once

#include <memory> // shared ptr
#include <string> // std::string and to_string

#include "nav_msgs/msg/odometry.hpp" // nav_msgs::msg::Odometry
#include "rclcpp/rclcpp.hpp" // node, init, spin, shutdown, RCLCPP_INFO (#define)
#include "sensor_msgs/msg/point_cloud2.hpp" // sensor_msgs::msg::PointCloud2
#include "std_msgs/msg/string.hpp"          // std_msgs::msg::String

class BagStats : public rclcpp::Node {
public:
  BagStats();

private:
  void chassis_odom_callback_(const nav_msgs::msg::Odometry::SharedPtr msg);
  void front_lidar_callback_(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void stats_callback() const;

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr chassis_odom_sub_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr
      front_lidar_sub_;

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr stats_pub_;
  rclcpp::TimerBase::SharedPtr stats_timer_;
  mutable std::mutex stats_mutex_;

  // DEFAULT stats_period parameter value
  int stats_period_ms_{100};  // 1 ms is generally the minimum accurate value
  
  // stats to protect with the lockguard:
  size_t odom_count_{};
  size_t points_count_{};
  //
  // pose.pose.position
  double last_x_{};
  double last_y_{};
  double total_distance_{};
  // twist.twist.linear
  double total_speed_{};
  double average_speed_{};
  // twist.twist.angular
  double max_turn_{};
  //
  // width * height
  size_t total_points_{};
  double average_points_{};
  size_t max_points_{};
};
