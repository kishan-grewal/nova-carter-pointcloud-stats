#include <chrono>                     // std::chrono::milliseconds
using namespace std::chrono_literals; // using namepsace -> convenient syntax
// e.g. stop including (std) or use suffix like ms (chrono)

#include <memory> // shared ptr
#include <string> // std::string and to_string

#include "rclcpp/rclcpp.hpp" // node, init, spin, shutdown, RCLCPP_INFO (#define)
#include "std_msgs/msg/string.hpp" // std_msgs::msg::String

class MyPublisher : public rclcpp::Node {
public:
  MyPublisher() : Node("my_publisher") {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(1000ms, [this]() { this->callback(); });
  }

private:
  void callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello World!";
    RCLCPP_INFO(this->get_logger(), message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

// will always be like this
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}
