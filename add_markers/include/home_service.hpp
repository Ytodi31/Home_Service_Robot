#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

class home_service{
public:
  visualization_msgs::Marker marker;
  ros::Publisher marker_pub;
  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
};
