/*
 * camera_message.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: eric
 */

#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

static const char WINDOW[] = "Image window";
static void help() {
	printf(
			"\nThis program demonstrates converting OpenCV Image to ROS Image messages  \n");

}

int readVideo() {

}

int main(int argc, char** argv) {
	ros::init(argc, argv, "image_converter");
	cv::VideoCapture cap(0); // open the default camera 640*480
	if (!cap.isOpened())  // check if we succeeded
	{
		//std::cout << "failed to open camera" << std::endl;
		return -1;
	}

	ros::NodeHandle node;
	image_transport::ImageTransport transport(node);
	image_transport::Publisher image_pub;
	image_pub = transport.advertise("/cam0/image_raw", 0);

	cv::Mat cv_image;
	cv::namedWindow("edges", 1);
	for (;;) {
		cv::Mat frame;
		cap >> frame; // get a new frame from camera
		//edges = frame;
		//cd cvtColor(frame, edges,CV_BGR2GRAY);

		cv::cvtColor(frame, cv_image, CV_BGR2GRAY);
		//cap.VideoCapture(edges);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		cv::imshow("edges", cv_image);
		if (cv::waitKey(30) >= 0)
			break;

		if (cv_image.empty()) {
			ROS_ERROR("Read the picture failed!");
			return -1;
		}

		//Convert OpenCV image to ROS message

		ros::Time time = ros::Time::now();

		cv_bridge::CvImage cvi;
		cvi.header.stamp = time;
		cvi.header.frame_id = "image";
		cvi.encoding = "mono8";
		cvi.image = cv_image;

		sensor_msgs::Image im;
		cvi.toImageMsg(im);
		cout << "start publising" <<time<< "\n";
		image_pub.publish(im);
		cout << "Converted Successfully!" << time << "\n";
		//ROS_INFO("Converted Successfully!");
		//cv::waitKey(300);
	}

	ros::spin();
	return 0;
}

