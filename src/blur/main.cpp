#include <opencv2/opencv.hpp>

#include <cstdlib>


int main(int argc, char *argv[])
{
	cv::Mat srcImg = cv::imread("1.jpg");

	cv::imshow("模糊前", srcImg);

	// 模糊
	cv::Mat dstImg;

	cv::blur(srcImg, dstImg, cv::Size(7,7));

	cv::imshow("模糊后", dstImg);

	cv::waitKey(6000);

	exit(EXIT_SUCCESS);
}

