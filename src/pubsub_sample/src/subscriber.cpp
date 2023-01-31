// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <sample_msgs/msg/int32_stamped.hpp>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
      : Node("minimal_subscriber"), count_(0)
  {
    subscription_ = this->create_subscription<sample_msgs::msg::Int32Stamped>(
        "topic1", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    publisher_ = this->create_publisher<sample_msgs::msg::Int32Stamped>("topic2", 10);
  }

private:
  void topic_callback(const sample_msgs::msg::Int32Stamped &msg)
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg.data);

    auto message = sample_msgs::msg::Int32Stamped();
    message.data = msg.data * 2;
    message.stamp = msg.stamp;

    RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
    publisher_->publish(message);
  }

  rclcpp::Subscription<sample_msgs::msg::Int32Stamped>::SharedPtr subscription_;
  rclcpp::Publisher<sample_msgs::msg::Int32Stamped>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
