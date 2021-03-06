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

// common stl includes
#include <chrono>
#include <memory>

//include of the rclcpp libary, which is the cpp api
#include "rclcpp/rclcpp.hpp"
//include of the topic type that we will be publishing.
//include of msg does not have caps.
#include "first_package/msg/tint.hpp"

using namespace std::chrono_literals;
//TODO: figure out more about SharedPtr (https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c)
//TODO: figure out about bind function as well as the c++ function statement
//TODO: figure out about lamdas. https://www.variadic.xyz/2011/10/12/c11-lambda-having-fun-with-brackets/#.UJmXu8XA9Z8
//TODO: test out between calling using lamdas and boost bind.

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */
// inherit member functions from rclcpp:Node class
class MinimalPublisher : public rclcpp::Node
{
public:
  // call node function, to create a new node with the specified name
  MinimalPublisher()
  : Node("ros_pub_tint")
  { //initialise publisher pointer, by calling create publisher function which returns a shared ptr of a new publisher object instance
    publisher_ = this->create_publisher<first_package::msg::Tint>("cone", 10);

    //init the timer ptr with a wall timer object.

    timer_ = this->create_wall_timer(
      500ms, [this](){
        // create string obj.
        auto message = first_package::msg::Tint();
        message.num = this->count;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
        //publish message
        publisher_->publish(message);
        this->count++;
      });
  }

private:
  int count=0;
  //shared ptr of a timer
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<first_package::msg::Tint>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
