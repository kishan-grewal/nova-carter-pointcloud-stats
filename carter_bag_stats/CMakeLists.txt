cmake_minimum_required(VERSION 3.8)
project(carter_bag_stats)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies e.g. rclcpp, std_msgs
find_package(ament_cmake REQUIRED)
# my additions:
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# add executable like normal cpp
add_executable(bag_stats
  src/main.cpp
)

# standard, tell compiler where to find headers
target_include_directories(bag_stats PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# link to the found packages (excluding ament_cmake)
ament_target_dependencies(bag_stats
  rclcpp
  std_msgs
)

# standard, add to install dir so ros2 run can find it
install(TARGETS bag_stats
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
