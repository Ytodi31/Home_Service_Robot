#!/bin/sh

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/myworld.world" &
sleep 8
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 8
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun pick_objects pick_objects" &
sleep 5
