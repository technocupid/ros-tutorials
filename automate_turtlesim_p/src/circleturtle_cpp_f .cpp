#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include "turtlesim/Pose.h"

bool is_turtle_outside;

void cpp_callback(turtlesim::Pose pose_message){
	is_turtle_outside = (pose_message.x<2) || (pose_message.x>8) ||
				(pose_message.y<2) || (pose_message.y>8);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "circleturtle_cpp_n");
	ros::NodeHandle nh;
	ros::Publisher vel_pub_cpp = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
	ros::Subscriber pose_sub_cpp = nh.subscribe("turtle1/pose", 10, cpp_callback);

	ros::Rate loop_rate(20);

	geometry_msgs::Twist  velocity_v;
	velocity_v.linear.x = 1;
	//velocity_v.angular.z = 1;

	while(ros::ok())
	{
		//velocity_v.angular.z = (double)rand() / (double)RAND_MAX;
		if(is_turtle_outside)
			velocity_v.angular.z = 1;
		else
			velocity_v.angular.z = 0;		
		
		vel_pub_cpp.publish(velocity_v);
		loop_rate.sleep();

		ros::spinOnce();
	}
	return 0;
}
