#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pub_cpp_n");
	ros::NodeHandle nh;
	ros::Publisher pub_handle_cpp = nh.advertise<std_msgs::String>("my_first_t", 10);
	std_msgs::String hello_v;
	hello_v.data = "Hello from C++";
	ros::Rate loop_hz(10);

	while(ros::ok())
	{
		pub_handle_cpp.publish(hello_v);
		ROS_INFO_STREAM(hello_v.data);
		loop_hz.sleep();
	}
	return 0;
}
