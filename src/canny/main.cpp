#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

#include <cstdlib>


int main(int argc, char *argv[])
{
	cv::Mat srcImg = cv::imread("1.jpg");

	cv::imshow("模糊前", srcImg);

	// 模糊
	cv::Mat dstImg, grayImg, edgeImg;

	// 创建同样的矩阵
	dstImg.create(srcImg.size(), srcImg.type());

	// 灰度图像
	cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

	cv::blur(grayImg, edgeImg, cv::Size(3,3));
	// 边缘检测
	cv::Canny(edgeImg, edgeImg, 3, 9, 3);

	cv::imshow("边缘检测", edgeImg);

	cv::waitKey(6000);

	exit(EXIT_SUCCESS);
}

