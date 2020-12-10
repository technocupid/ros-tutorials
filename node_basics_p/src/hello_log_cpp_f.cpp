#include "ros/ros.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "hello_log_cpp_n");
	ros::NodeHandle n;
	ros::Rate loop_hz(10);

	while(ros::ok())
	{
		ROS_INFO_STREAM("Hello from C++");
		loop_hz.sleep();
	}
	return 0;
}
