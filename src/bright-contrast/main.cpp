/*
 *   改变对比度和亮度
 *
 *
 */

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>


static const char* window_name_dst="change bright contrast";
static const char* window_name_src="原始图";

static int contrast_value = 0;
static int bright_value = 0;

static cv::Mat srcMat;
static cv::Mat dstMat;

static void contrast_bright_callback(int pos, void* userdata)
{
	cv::namedWindow(window_name_src, cv::WINDOW_AUTOSIZE);

	for(int r = 0; r < srcMat.rows; r++)
	{
		for(int c = 0; c < srcMat.cols; c++)
		{
			for(int s = 0; s < 3; s++)
			{
				dstMat.at<cv::Vec3b>(r, c)[s] = cv::saturate_cast<uchar>((contrast_value * 0.01) * (srcMat.at<cv::Vec3b>(r, c)[s]) + bright_value);
			}
		}
	}

	cv::imshow(window_name_src, srcMat);
	cv::imshow(window_name_dst, dstMat);
}

int main(int argc, char *argv[])
{
	srcMat = cv::imread("/home/lwg/opencv/opencv/build/debug/bin/dota_jugg.jpg");
	dstMat = cv::Mat::zeros(srcMat.size(), srcMat.type());

	cv::namedWindow(window_name_dst, cv::WINDOW_AUTOSIZE);

	contrast_value = 80;
	bright_value = 80;

	int n = cv::createTrackbar("对比度:", window_name_dst, &contrast_value, 300, contrast_bright_callback);
	int m = cv::createTrackbar("亮度:", window_name_dst, &bright_value, 200, contrast_bright_callback);

	std::cout << "m="<<m << " n=" << n << std::endl;

	contrast_bright_callback(contrast_value, NULL);

	while(char(cv::waitKey(1)) != 'q')
	{

	};
	exit(EXIT_SUCCESS);
}

