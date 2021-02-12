#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
class VideoFile
{
	public:
		VideoFile();
		int open(cv::String pathname);
		int play();
		int pause();
		int videoSetFrame(int frame);
		bool isOpened();
	private: 
		cv::VideoCapture cam;
};


		