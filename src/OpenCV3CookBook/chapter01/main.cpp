#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>
#include <random>


/*
https://github.com/laganiere
*/

#define SHOW_IMAGE "Show Image"
#define OUT_IMAGE "Out Image"

void onMouseShowImage(int event, int x, int y, int flags, void *param)
{
	std::cout << event << "(" << x << "," << y << ")" << std::endl;

	switch (event)
	{
	case cv::EVENT_LBUTTONDOWN:

		break;

	case cv::EVENT_LBUTTONUP:
		break;

	case cv::EVENT_RBUTTONUP:
		break;

	case cv::EVENT_RBUTTONDOWN:
		break;

	case cv::EVENT_MOUSEMOVE:
		break;
	}
}

void test_image()
{
	// 读取灰度图片 cv::IMREAD_GRAYSCALE
	// 读取原图     cv::IMREAD_COLOR
	cv::Mat image = cv::imread("1.jpg", cv::IMREAD_COLOR);
	if (image.empty())
	{
		exit(EXIT_FAILURE);
	}

	std::cout << "row " << image.rows << " col " << image.cols << std::endl;
	std::cout << "channel " << image.channels() << std::endl; // 原图的通道数

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, image);

	cv::setMouseCallback(SHOW_IMAGE, onMouseShowImage, reinterpret_cast<void*>(&image));

	// 翻转图片
	cv::Mat result;
	cv::flip(image, result, cv::ROTATE_180);

	cv::namedWindow(OUT_IMAGE);
	cv::imshow(OUT_IMAGE, result);

	cv::imwrite("output.jpg", result);
}

void test_roi()
{
	cv::Mat srcImage = cv::imread("1.jpg", cv::IMREAD_COLOR);

	if (srcImage.empty())
	{
		exit(EXIT_FAILURE);
	}

	cv::Mat logImage = cv::imread("logo.jpg", cv::IMREAD_GRAYSCALE);

	if (logImage.empty())
	{
		exit(EXIT_FAILURE);
	}

	std::cout << logImage.rows << "," << logImage.cols;

	// 感兴趣的区域， Region of interesting
	cv::Mat roiImage(srcImage,
		cv::Rect(srcImage.cols - logImage.cols, 
			     srcImage.rows - logImage.rows, 
			     logImage.cols, logImage.rows));

	// 掩码
	cv::Mat mask(logImage);

	logImage.copyTo(roiImage, mask);

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, srcImage);
}

// 椒盐噪声
void salt(cv::Mat image, int num)
{
	std::default_random_engine engine;
	std::uniform_int_distribution<int> randon_row(0, image.rows - 1);
	std::uniform_int_distribution<int> randon_col(0, image.cols - 1);

	int i, j;
	for (int k = 0; k < num; k++)
	{
		// 随机生存位置
		i = randon_col(engine);
		j = randon_row(engine);

		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(j, i) = 255;
		}
		else
		{
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
			// 或者
			// image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
		}
	}
}

// 测试椒盐噪声
void test_salt_and_pepper_noise()
{
	cv::Mat srcImage = cv::imread("boldt.jpg", cv::IMREAD_COLOR);

	if (srcImage.empty())
	{
		exit(EXIT_FAILURE);
	}

	salt(srcImage, 1000);

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, srcImage);
}

// 减色函数，取整
void reduce_color(cv::Mat image, int div=64)
{
	// 行数
	int rows = image.rows;
	// 每行字节数
	int cols_num = image.cols * image.channels();

	// 每行字节数
	size_t step = image.step;

	// 每个像素元素个数
	size_t elemSize = image.elemSize();

	for (int i = 0; i < rows; i++)
	{
		// 第 i 行数据
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < cols_num; j++)
		{
			// 处理每个像素，整除运算
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
// 取余
void reduce_color2(cv::Mat image, int div = 64)
{
	// 行数
	int rows = image.rows;

	// 每行字节数
	size_t step = image.step;

	for (int i = 0; i < rows; i++)
	{
		// 第 i 行数据
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// 处理每个像素, 取模运算
			data[j] = data[j] - data[j] % div + div / 2;
		}
	}
}
// 取整, 优化版本
void reduce_color3(cv::Mat image, int div = 64)
{
	// 行数
	int rows = image.rows;

	// 每行字节数
	size_t step = image.step;

	uchar div2 = div >> 1; // div / 2

	for (int i = 0; i < rows; i++)
	{
		// 第 i 行数据
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// 处理每个像素，整除运算
			*data++ = *data / div * div + div2;
		}
	}
}

// 位运算
void reduce_color4(cv::Mat image, int div = 64)
{
	// 行数
	int rows = image.rows;

	// 每行字节数
	size_t step = image.step;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

	uchar div2 = div >> 1; // div / 2

	uchar mask = 0xFF << n;

	for (int i = 0; i < rows; i++)
	{
		// 第 i 行数据
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// 处理每个像素，整除运算
			data[j] &= mask;
			data[j] += div2;

			//*data &= mask;
			//*data++ += div2; // 
		}
	}
}


// 位运算
void reduce_color5(cv::Mat image, int div = 64)
{
	// 行数
	int rows = image.rows;

	// 每行字节数
	size_t step = image.step;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

	uchar div2 = div >> 1; // div / 2

	uchar mask = 0xFF << n;

	for (int i = 0; i < rows; i++)
	{
		// 第 i 行数据
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// 处理每个像素
			*data &= mask;
			*data++ += div2; // 
		}
	}
}


void test_reduce_color()
{
	cv::Mat srcImage = cv::imread("boldt.jpg", cv::IMREAD_COLOR);

	if (srcImage.empty())
	{
		exit(EXIT_FAILURE);
	}

	reduce_color4(srcImage);

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, srcImage);
}

int main(int argc, char *argv[])
{
	
	//test_roi();
	//test_salt_and_pepper_noise();
	test_reduce_color();

	cv::waitKey(0);

	exit(EXIT_SUCCESS);
}



