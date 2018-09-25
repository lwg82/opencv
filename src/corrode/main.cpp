#include <opencv2/opencv.hpp>

#include <cstdlib>


int main(int argc, char *argv[])
{
	cv::Mat srcImg = cv::imread("1.jpg");

	cv::imshow("腐蚀前", srcImg);

	// 腐蚀
	cv::Mat elem = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

	cv::Mat dstImg;

	cv::erode(srcImg, dstImg, elem);

	cv::imshow("腐蚀后", dstImg);

	cv::waitKey(6000);

	exit(EXIT_SUCCESS);
}

