cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub_message_filter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

add_executable(talker src/publisher.cpp)
ament_target_dependencies(talker rclcpp std_msgs sample_msgs)

add_executable(listener src/subscriber.cpp)
ament_target_dependencies(listener rclcpp std_msgs sample_msgs)

add_executable(sync_listener src/subscriber_sync.cpp)
ament_target_dependencies(sync_listener rclcpp std_msgs sample_msgs message_filters)

install(TARGETS
  talker
  listener
  sync_listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
