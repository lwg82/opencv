/*
 *   图像混合
 *
 *
 */

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>

// 区域混合
void blend_simple()
{
	cv::Mat img_log = cv::imread("dota_logo.jpg");
		cv::Mat img_background = cv::imread("dota_pa.jpg");

		// 定义 ROI 区域
		cv::Mat img_roi = img_background(cv::Rect(200, 250, img_log.cols, img_log.rows)); // 注意这里的 cols, rows

		// 加载灰度图
		cv::Mat mask = cv::imread("dota_logo.jpg", cv::IMREAD_GRAYSCALE);

		img_log.copyTo(img_roi, mask);

		cv::imshow("blend image", img_background);
}

// 线性混合  linear blending
void linear_blending()
{
	double alpha = 0.5;
	double beta = 1.0 - alpha;
	double gamma = 0.0;
	cv::Mat dstImg;

	cv::Mat src1 = cv::imread("mogu.jpg");
	cv::Mat src2 = cv::imread("rain.jpg");

	cv::addWeighted(src1, alpha, src2, beta, gamma, dstImg);

	cv::imshow("原图", src2);
	cv::imshow("效果图", dstImg);
}
// 将 roi 和 linear blending 混合使用
void roi_linear_blending()
{
	double alpha = 0.5;
	double beta = 0.3;
	double gamma = 0.0;
	//cv::Mat dstImg;

	cv::Mat src1 = cv::imread("dota_pa.jpg");
	cv::Mat src2 = cv::imread("dota_logo.jpg");

	//cv::Mat roi = src1(cv::Range(200,250, src2.cols, src2.rows));
	cv::Mat roi = src1(cv::Range(250, 250+src2.rows), cv::Range(200, 200+src2.cols));

	cv::addWeighted(roi, alpha, src2, beta, gamma, roi);

	cv::imshow("效果图", src1);
}

// 通道分离
void channel_split()
{
	// 蓝色通道分离
	cv::Mat src1 = cv::imread("dota_jugg.jpg");
	cv::Mat blue_channel;
	cv::Mat green_channel;
	cv::Mat red_channel;

	std::vector<cv::Mat> channels;

	cv::split(src1, channels);

	blue_channel = channels.at(0);
	green_channel = channels.at(1);
	red_channel = channels.at(2);

	cv::imshow("blue channel", blue_channel);
	cv::imshow("green channel", green_channel);
	cv::imshow("red channel", red_channel);
}

// 通道分离于合成
void channel_split_merge()
{
	cv::Mat src1 = cv::imread("/home/lwg/opencv/opencv/build/debug/bin/dota_jugg.jpg");
	cv::Mat src2 = cv::imread("/home/lwg/opencv/opencv/build/debug/bin/dota_logo.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat blue_channel;
	cv::Mat green_channel;
	cv::Mat red_channel;

	std::vector<cv::Mat> channels;

	double alpha = 1.0;
	double beta = 0.5;
	double gamma = 0.0;

	cv::split(src1, channels);

	blue_channel = channels.at(0);
	green_channel = channels.at(1);
	red_channel = channels.at(2);

	cv::Mat roi_blue = blue_channel(cv::Rect(500, 250, src2.cols, src2.rows));
	cv::Mat roi_green = green_channel(cv::Rect(380, 70, src2.cols, src2.rows));
	cv::Mat roi_red = red_channel(cv::Rect(600, 70, src2.cols, src2.rows));


	try
	{
		cv::addWeighted(roi_blue, alpha, src2, beta, gamma, roi_blue);
		cv::addWeighted(roi_green, alpha, src2, beta, gamma, roi_green);
		cv::addWeighted(roi_red, alpha, src2, beta, gamma, roi_red);
	}
	catch(cv::Exception &ex)
	{
		std::cout << ex.msg << std::endl;
	}
	cv::merge(channels, src1);

	cv::imshow("blue channel", src1);
}

int main(int argc, char *argv[])
{
	//roi_linear_blending();

	//channel_split();
	channel_split_merge();

	cv::waitKey(0);
	exit(EXIT_SUCCESS);
}

