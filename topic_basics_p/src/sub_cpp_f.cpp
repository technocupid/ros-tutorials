#include "ros/ros.h"
#include "std_msgs/String.h"

void cpp_clbk(std_msgs::String received_msg)
{
	ROS_INFO_STREAM("I heard : " << received_msg.data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "sub_cpp_n");
	ros::NodeHandle nh;
	ros::Subscriber sub_handle_cpp = nh.subscribe("my_first_t", 10, cpp_clbk);
	ros::spin();
	return 0;
}
