#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::Mat mat(3, 2, CV_32F);

	cv::randu(mat, cv::Scalar::all(0), cv::Scalar::all(255));

	std::cout << mat << std::endl; // opencv 标准输出格式
	std::cout << cv::format(mat, cv::Formatter::FMT_PYTHON) << std::endl;

	//cv::Mat mat_ones = cv::Mat::ones(3,4, CV_32F);

	//std::cout << mat_ones << std::endl;;

	//cv::Mat mat_eye = cv::Mat::eye(4, 4, CV_32F);

	//std::cout << mat_eye << std::endl;

	//mat.create(3, 10, CV_32FC3);

	cv::Point p;
	cv::Mat img, dstImg;

	// img = cv::imread("1.jpg", cv::IMREAD_GRAYSCALE); // 加载灰度图
	// img = cv::imread("1.jpg", cv::IMREAD_ANYDEPTH | cv::IMREAD_ANYCOLOR); // 无损的原图

	img = cv::imread("1.jpg");
	cv::cvtColor(img, dstImg, cv::COLOR_BGR2Lab);

	cv::imshow("1.jpg", dstImg);

	cv::waitKey(6000);

	exit(EXIT_SUCCESS);
}

