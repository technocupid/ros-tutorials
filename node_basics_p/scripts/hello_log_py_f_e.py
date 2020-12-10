#!/usr/bin/python

import rospy

rospy.init_node("hello_log_py_n")
loop_hz = rospy.Rate(10)

while not rospy.is_shutdown():
	rospy.loginfo("Hello from Python")
	loop_hz.sleep()




