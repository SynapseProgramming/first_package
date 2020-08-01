cmake_minimum_required(VERSION 3.5)
project(first_package)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) 

#add executables
add_executable(talkerog src/publisher_member_function.cpp)
ament_target_dependencies(talkerog rclcpp std_msgs)

add_executable(talkerlamda src/publisher_lamda.cpp)
ament_target_dependencies(talkerlamda rclcpp std_msgs)


add_executable(subog src/subscriber_member_function.cpp)
ament_target_dependencies(subog rclcpp std_msgs)

add_executable(sublamda src/sublamda.cpp)
ament_target_dependencies(sublamda rclcpp std_msgs)

#key in name here, for ro2 to find the executable
install(TARGETS
  sublamda
  talkerog
  talkerlamda
  subog
  DESTINATION lib/${PROJECT_NAME})



ament_package()
