#!/usr/bin/python

import rospy
from std_msgs.msg import String

rospy.init_node("pub_py_n")
pub_handle_py = rospy.Publisher("my_first_t", String, queue_size=10)
hello_v = String()
hello_v.data = "Hello from Python"
loop_hz = rospy.Rate(5)

while not rospy.is_shutdown():
	pub_handle_py.publish(hello_v)
	rospy.loginfo(hello_v.data)
	loop_hz.sleep()

