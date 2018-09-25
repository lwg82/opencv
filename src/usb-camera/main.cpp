#include <opencv2/opencv.hpp>

#include <cstdlib>


int main(int argc, char *argv[])
{
	cv::VideoCapture videoCapture(0);
	cv::Mat srcFrame, edgeFrame;

	while(true)
	{
		// 读取一帧
		videoCapture >> srcFrame;

		// 灰度图像
		cv::cvtColor(srcFrame, edgeFrame, cv::COLOR_BGR2GRAY);

		// 3x3 内核降噪 2x3+1=7
		cv::blur(edgeFrame, edgeFrame, cv::Size(7,7));

		//
		cv::Canny(edgeFrame, edgeFrame, 0, 30, 3);

		cv::imshow("边缘检测", edgeFrame);

		if(cv::waitKey(30) >= 0)
			break;
	}

	exit(EXIT_SUCCESS);
}

