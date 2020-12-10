#!/usr/bin/python
import rospy
from msgsrv_basics_p.srv import WarningSwitch, WarningSwitchResponse

def warningClbk(warningReq):
	service_response_v = WarningSwitchResponse()
	if(warningReq.req_msg):
		rospy.loginfo('Warning Received')
		service_response_v.res_msg.data = 'Warning Acknowledged by the Server'
		return service_response_v
	else:
		rospy.loginfo('Normalcy Status Received')
		service_response_v.res_msg.data = 'Normalcy Acknowledged by the Server'
		return service_response_v		


rospy.init_node('serv_warning_py_n')
warning_server_py = rospy.Service('my_robot_warning_s', WarningSwitch, warningClbk)

rospy.spin()
