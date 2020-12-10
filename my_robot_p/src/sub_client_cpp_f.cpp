#include "ros/ros.h"
#include "msgsrv_basics_p/RobotStatus.h"
#include "msgsrv_basics_p/WarningSwitch.h"

#define THRESH 1900

bool warningCondition = false, warningConditionPrev = false;
void statusCallback (msgsrv_basics_p::RobotStatus statusMsg){
  if(statusMsg.motor1_rpm > THRESH ||
     statusMsg.motor2_rpm > THRESH ||
     statusMsg.motor3_rpm > THRESH ||
     statusMsg.motor4_rpm > THRESH)
	warningCondition = true;
  else
	warningCondition = false;

}


int main(int argc, char **argv){

  ros::init(argc, argv, "sub_client_cpp_n");
  ros::NodeHandle nh;
  ros::Subscriber sub_handle = nh.subscribe("my_robot_status_t", 10, statusCallback);

  ros::ServiceClient client_handle = 
		nh.serviceClient<msgsrv_basics_p::WarningSwitch>("my_robot_warning_s");
  client_handle.waitForExistence();
  msgsrv_basics_p::WarningSwitch warning_v;

  while(ros::ok()){
	if((warningCondition==true) && (warningConditionPrev==false)){
		ROS_INFO_STREAM("Sending Warning to Server");
		warning_v.request.req_msg = warningCondition;
		client_handle.call(warning_v);
		ROS_INFO_STREAM(warning_v.response.res_msg.data);
	}

	else if ((warningCondition==false) && (warningConditionPrev==true)){
		ROS_INFO_STREAM("Sending Normalcy Status to Server");
		warning_v.request.req_msg = warningCondition;
		client_handle.call(warning_v);
		ROS_INFO_STREAM(warning_v.response.res_msg.data);
	}

	warningConditionPrev = warningCondition;
	ros::spinOnce();
  }
  return 0;
}
