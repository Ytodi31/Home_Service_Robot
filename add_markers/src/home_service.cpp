#include "../include/home_service.hpp"

void home_service::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  float x, y;
  x = msg->pose.pose.position.x;
  y = msg->pose.pose.position.y;

  if ((x<=-5.6 && x>=-5.8) && (y<=5.2 && y>=5.0)) {
    marker.action = visualization_msgs::Marker::DELETE;
    ros::Duration(1.5).sleep();
    marker_pub.publish(marker);
    ROS_INFO_ONCE("Hooray, the robot has picked up the object");
  }

if((x<=8.5 && x>=7.5) && (y<=-3.8 &&  y>=-4.2)) {
    marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 7;
    marker.pose.position.y = -4.1;
    marker.pose.position.z = 0;
    marker.pose.orientation.w = 1.0;
    marker_pub.publish(marker);
    ROS_INFO_ONCE("Hooray, the robot has dropped off the object");
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "home_service");
  ros::NodeHandle n;
  ros::Rate r(1);
  home_service robot;
  robot.marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber loc_sub = n.subscribe("/odom", 100, &home_service::odomCallback, &robot);
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while(ros::ok()){


    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    robot.marker.header.frame_id = "/map";
    robot.marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    robot.marker.ns = "basic_shapes";
    robot.marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    robot.marker.type = shape;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    robot.marker.scale.x = 0.5;
    robot.marker.scale.y = 0.5;
    robot.marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    robot.marker.color.r = 1.0f;
    robot.marker.color.g = 0.0f;
    robot.marker.color.b = 0.0f;
    robot.marker.color.a = 1.0;

    robot.marker.pose.orientation.x = 0.0;
    robot.marker.pose.orientation.y = 0.0;
    robot.marker.pose.orientation.z = 0.0;

    robot.marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    robot.marker.pose.position.x = -6.2;
    robot.marker.pose.position.y = 5.6;
    // robot.marker.pose.position.x = -6.3;
    // robot.marker.pose.position.y = 5.2;
    robot.marker.pose.position.z = 0;
    robot.marker.pose.orientation.w = 1.0;

    robot.marker.lifetime = ros::Duration();

    // Publish the marker
    while (robot.marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    robot.marker_pub.publish(robot.marker);

    ros::spin();
  }
}
