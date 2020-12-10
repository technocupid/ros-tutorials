#!/usr/bin/python
import rospy
from msgsrv_basics_p.msg import RobotStatus
import csv

rospy.init_node('pub_status_py_n')
status_pub_py = rospy.Publisher('my_robot_status_t', RobotStatus, queue_size = 10)
loop_rate = rospy.Rate(1)

fileName = "/home/mky/Desktop/ros_ws/src/my_robot_p/data/rpm_locn_data.csv"
csvFile = open(fileName, 'r')
csvreader = csv.reader(csvFile)

status_v = RobotStatus()

while not rospy.is_shutdown():

	row = next(csvreader)
	status_v.motor1_rpm = int(row[0])
	status_v.motor2_rpm = int(row[1])
	status_v.motor3_rpm = int(row[2])
	status_v.motor4_rpm = int(row[3])
	status_v.locn.x = float(row[4])
	status_v.locn.y = float(row[5])
	status_v.locn.z = float(row[6])

	status_pub_py.publish(status_v)
	rospy.loginfo(status_v)

	loop_rate.sleep()

