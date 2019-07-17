#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <math.h>
float pick_x = 2.8;
float pick_y = 2.0;
float drop_x = 2.8;
float drop_y = 4.0; 
bool pick_flag = false;
bool drop_flag = false;
float dist_threshold = 0.5;

void callback_odom(const nav_msgs::Odometry::ConstPtr &msg) 
{
float robot_pose_x = msg-> pose.pose.position.x;
float robot_pose_y = msg-> pose.pose.position.y;
float dist_pick = 0.0 ;
float dist_drop = 0.0;
 //caluclate distance between robot's pose and pick up location 
dist_pick = sqrt(pow((pick_x-robot_pose_x),2)+ pow((pick_y-robot_pose_y),2));
//calculate  distance between robot's pose and drop off location 
dist_drop = sqrt(pow((drop_x-robot_pose_x),2)+ pow((drop_y-robot_pose_y),2));

if ( !pick_flag && !drop_flag)
{//check distance between robot's pose and pick up location 
 if (dist_pick <= dist_threshold)
      {	pick_flag = true;
      ROS_INFO("reached pick up location");
      }
}

if (pick_flag && !drop_flag)
{//check distance between robot's pose and pick up location 
 if (dist_drop <= dist_threshold)
      { drop_flag = true; 
      ROS_INFO("reached drop off location");
      }
}


}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //Define a subcriber 
  ros::Subscriber odom_subscriber = n.subscribe("/odom",1000,callback_odom);
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one

    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER

    marker.type = shape;


    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)

    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    // Set the marker at the pick up location

    marker.pose.position.x = pick_x;
    marker.pose.position.y = pick_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;


    // Set the scale of the marker -- 1x1x1 here means 1m on a side

    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;


    // Set the color -- be sure to set alpha to something non-zero!

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;


    marker.lifetime = ros::Duration();
//  while (ros::ok())
//  {


    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
   // marker_pub.publish(marker);

    // Create a cube shape
    

    // if pick_flag is true , make the shape diappear 
   if(pick_flag) 
   {
    marker.action = visualization_msgs::Marker::DELETE;
    ROS_INFO("picking up the object");
    //marker_pub.publish(marker);

    ros::Duration(5.0).sleep();
   } 
   // if drop_flag is true, make the shape appear 
   if(drop_flag)  
   { 
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = drop_x;
    marker.pose.position.y = drop_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;


    ROS_INFO("dropping off the object");
    //marker_pub.publish(marker);

   // ros::Duration(5.0).sleep();
   }


   marker_pub.publish(marker);
   ros::spinOnce();
//   r.sleep();
  }
  return 0; 
}

