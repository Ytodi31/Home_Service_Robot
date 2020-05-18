#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Cleint to send goal requests to move_base_server through SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
// Initialize node
 ros::init(argc, argv, "pick_objects");

// spin a thread by defaukt with action client
 MoveBaseClient ac("move_base", true);

 // Wait 5 sec for move_base action server to come up
 while(!ac.waitForServer(ros::Duration(5.0))){
   ROS_INFO("Waiting for the move_base action server to come up");
 }

 move_base_msgs::MoveBaseGoal goal;

 goal.target_pose.header.frame_id = "map";
 goal.target_pose.header.stamp = ros::Time::now();

 // Define a position and orientation for the robot to reach

  goal.target_pose.pose.position.x = -5.25;
  goal.target_pose.pose.position.y = 6.2;
// goal.target_pose.pose.position.x = 1;
 goal.target_pose.pose.orientation.w = 1.0;

 ROS_INFO("Sending robot to pickup location");
 ac.sendGoal(goal);

 ac.waitForResult();

 if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
   ROS_INFO("Hooray, the robot reached the pickup location");
 else
   ROS_INFO("The robot has failed to reach the pickup location");

  ros::Duration(5).sleep();
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 7.7;
   goal.target_pose.pose.position.y = -3.0;
  goal.target_pose.pose.orientation.w = 1.0;


   ROS_INFO("Sending goal");
   ac.sendGoal(goal);

   ac.waitForResult();

   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     ROS_INFO("Hooray, the robot reached the pickup location");
   else
     ROS_INFO("The robot has failed to reach the pickup location");
  ros::Duration(1).sleep();
  return 0;
}
