#include <chrono>
#include <functional>
#include <memory>
#include <string>

// #include "../include/mapping.hpp"
#include "../include/mapping_node.hpp"

using namespace std::chrono_literals;

MappingNode::MappingNode() : Node("mapping"), count_(0)
{
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic_out", 10);
    // subscription_ = this->create_subscription<std_msgs::msg::String>(
    //     "topic", 10, std::bind(&mapping::topic_callback, this, std::placeholders::_1));
    timer_ = this->create_wall_timer(5000ms, std::bind(&MappingNode::timer_callback, this));
}

MappingNode::~MappingNode()
{
}

void MappingNode::timer_callback()
{
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}

void MappingNode::topic_callback(const std_msgs::msg::String &msg) const
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
}