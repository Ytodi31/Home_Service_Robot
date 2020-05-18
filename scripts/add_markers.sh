#!/bin/sh
export TURTLEBOT_GAZEBO_MAP_FILE=/home/ytodi31/my_ws/src/map/map.yaml
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/myworld.world" &
sleep 8
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 8
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun add_markers add_markers" &
sleep 5
