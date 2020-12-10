#include "ros/ros.h"
#include "msgsrv_basics_p/WarningSwitch.h"


bool serviceCallback(msgsrv_basics_p::WarningSwitch::Request &requestMsg,
			msgsrv_basics_p::WarningSwitch::Response &responseMsg){
  if(requestMsg.req_msg){
	ROS_INFO_STREAM("Warning Received");
	responseMsg.res_msg.data="Warning Acknowledged by Server";
  }
  else{
	ROS_INFO_STREAM("Normalcy Status Received");
	responseMsg.res_msg.data = "Normalcy Status Acknowledged by Server";
  }
  return true;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "serv_warning_cpp_n");
  ros::NodeHandle nh;
  ros::ServiceServer service_handle = nh.advertiseService("my_robot_warning_s", serviceCallback);
  ros::spin();
  return 0;
}
