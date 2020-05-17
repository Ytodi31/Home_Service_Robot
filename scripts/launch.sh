#!/bin/sh

xterm -e "gazebo" &
sleep 5
xterm -e "roscore" &
sleep 5
xterm -e "rosrun rviz rviz"
