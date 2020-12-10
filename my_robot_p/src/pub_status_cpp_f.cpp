#include "ros/ros.h"
#include "msgsrv_basics_p/RobotStatus.h"
#include <fstream>
#include <sstream>

int main(int argc, char **argv){

  ros::init(argc, argv, "pub_status_cpp_n");
  ros::NodeHandle nh;
  ros::Publisher pub_handle = nh.advertise<msgsrv_basics_p::RobotStatus>("my_robot_status_t", 10);
  ros::Rate loop_rate(1);

  std::fstream fin;
  fin.open("/home/mky/Desktop/ros_ws/src/my_robot_p/data/rpm_locn_data.csv", std::ios::in);
  std::string line, word;

  msgsrv_basics_p::RobotStatus status_v;

  while(ros::ok() && !fin.eof()){

	getline(fin, line);
	std::stringstream s(line);

	getline(s, word, ',');
	status_v.motor1_rpm = std::stoi(word);

	getline(s, word, ',');
	status_v.motor2_rpm = std::stoi(word);

	getline(s, word, ',');
	status_v.motor3_rpm = std::stoi(word);

	getline(s, word, ',');
	status_v.motor4_rpm = std::stoi(word);

	getline(s, word, ',');
	status_v.locn.x = std::stoi(word);

	getline(s, word, ',');
	status_v.locn.y = std::stoi(word);

	getline(s, word, ',');
	status_v.locn.z = std::stoi(word);

	pub_handle.publish(status_v);
	ROS_INFO_STREAM(status_v.motor1_rpm << " "<<
		status_v.motor2_rpm << " "<<
		status_v.motor3_rpm << " "<<
		status_v.motor4_rpm << " "<<
		status_v.locn.x << " "<<
		status_v.locn.y << " "<<
		status_v.locn.z );

	loop_rate.sleep();
  }

return 0;
}
