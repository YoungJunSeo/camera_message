cmake_minimum_required(VERSION 2.8.3)
project(camera_message)

## Find catkin macros and libraries

find_package(catkin  REQUIRED COMPONENTS cv_bridge image_transport  roscpp sensor_msgs std_msgs)
find_package(OpenCV REQUIRED)

## Declare a catkin package
catkin_package()

## Include directories,
## Add target and link libraries

include_directories(include ${OpenCV_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(camera_message_node src/camera_message.cpp)
target_link_libraries(camera_message_node ${catkin_LIBRARIES} ${OpenCV_LIBS})
#add_dependencies(camera_message_node camera_message_gencpp)
##