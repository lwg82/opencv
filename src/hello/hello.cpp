#include <opencv2/opencv.hpp>

#include <cstdlib>


int main(int argc, char *argv[])
{
	cv::Point p;
	cv::Mat img;

	img = cv::imread("1.jpg");

	cv::imshow("1.jpg", img);

	cv::waitKey(6000);

	exit(EXIT_SUCCESS);
}

