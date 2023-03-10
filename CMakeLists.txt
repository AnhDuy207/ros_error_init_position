cmake_minimum_required(VERSION 3.0.2)
project(error_init_pos)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  mavros_msgs
  roscpp
  std_msgs
  visualization_msgs
  roslaunch
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES error_init_pos
  CATKIN_DEPENDS geometry_msgs mavros_msgs roscpp std_msgs visualization_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

roslaunch_add_file_check(launch)

add_executable(marker_node src/marker.cpp)

target_link_libraries(marker_node
  ${catkin_LIBRARIES}
)