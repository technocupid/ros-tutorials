#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include "turtlesim/Pose.h"
#include "turtlesim/SetPen.h"

bool is_turtle_outside;
bool is_turtle_outside_prev;

void cpp_callback(turtlesim::Pose pose_message){
	is_turtle_outside = (pose_message.x<2) || (pose_message.x>8) ||
				(pose_message.y<2) || (pose_message.y>8);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "clientchangepen_cpp_n");
	ros::NodeHandle nh;
	ros::Publisher vel_pub_cpp = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
	ros::Subscriber pose_sub_cpp = nh.subscribe("turtle1/pose", 10, cpp_callback);
	ros::ServiceClient changepen_handle_cpp = nh.serviceClient<turtlesim::SetPen>("turtle1/set_pen");	
	changepen_handle_cpp.waitForExistence();


	ros::Rate loop_rate(20);

	geometry_msgs::Twist  velocity_v;
	velocity_v.linear.x = 1;
	//velocity_v.angular.z = 1;
	turtlesim::SetPen moveIn, moveOut;
	moveIn.request.r = 0;
	moveIn.request.g = 0;
	moveIn.request.b = 0;
	moveIn.request.width = 5;
	moveIn.request.off = 0;

	moveOut.request.r = 255;
	moveOut.request.g = 255;
	moveOut.request.b = 255;
	moveOut.request.width = 5;
	moveOut.request.off = 0;

	while(ros::ok())
	{
		//velocity_v.angular.z = (double)rand() / (double)RAND_MAX;
		if(is_turtle_outside)
			velocity_v.angular.z = 1;
		else
			velocity_v.angular.z = 0;		
		
		if(is_turtle_outside_prev==0 and is_turtle_outside==1)
			changepen_handle_cpp.call(moveOut);
		else if(is_turtle_outside_prev==1 and is_turtle_outside==0)
			changepen_handle_cpp.call(moveIn);

		is_turtle_outside_prev = is_turtle_outside;

		vel_pub_cpp.publish(velocity_v);
		loop_rate.sleep();

		ros::spinOnce();
	}
	return 0;
}
