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
	// ��ȡ�Ҷ�ͼƬ cv::IMREAD_GRAYSCALE
	// ��ȡԭͼ     cv::IMREAD_COLOR
	cv::Mat image = cv::imread("1.jpg", cv::IMREAD_COLOR);
	if (image.empty())
	{
		exit(EXIT_FAILURE);
	}

	std::cout << "row " << image.rows << " col " << image.cols << std::endl;
	std::cout << "channel " << image.channels() << std::endl; // ԭͼ��ͨ����

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, image);

	cv::setMouseCallback(SHOW_IMAGE, onMouseShowImage, reinterpret_cast<void*>(&image));

	// ��תͼƬ
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

	// ����Ȥ������ Region of interesting
	cv::Mat roiImage(srcImage,
		cv::Rect(srcImage.cols - logImage.cols, 
			     srcImage.rows - logImage.rows, 
			     logImage.cols, logImage.rows));

	// ����
	cv::Mat mask(logImage);

	logImage.copyTo(roiImage, mask);

	cv::namedWindow(SHOW_IMAGE);
	cv::imshow(SHOW_IMAGE, srcImage);
}

// ��������
void salt(cv::Mat image, int num)
{
	std::default_random_engine engine;
	std::uniform_int_distribution<int> randon_row(0, image.rows - 1);
	std::uniform_int_distribution<int> randon_col(0, image.cols - 1);

	int i, j;
	for (int k = 0; k < num; k++)
	{
		// �������λ��
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
			// ����
			// image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
		}
	}
}

// ���Խ�������
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

// ��ɫ������ȡ��
void reduce_color(cv::Mat image, int div=64)
{
	// ����
	int rows = image.rows;
	// ÿ���ֽ���
	int cols_num = image.cols * image.channels();

	// ÿ���ֽ���
	size_t step = image.step;

	// ÿ������Ԫ�ظ���
	size_t elemSize = image.elemSize();

	for (int i = 0; i < rows; i++)
	{
		// �� i ������
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < cols_num; j++)
		{
			// ����ÿ�����أ���������
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
// ȡ��
void reduce_color2(cv::Mat image, int div = 64)
{
	// ����
	int rows = image.rows;

	// ÿ���ֽ���
	size_t step = image.step;

	for (int i = 0; i < rows; i++)
	{
		// �� i ������
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// ����ÿ������, ȡģ����
			data[j] = data[j] - data[j] % div + div / 2;
		}
	}
}
// ȡ��, �Ż��汾
void reduce_color3(cv::Mat image, int div = 64)
{
	// ����
	int rows = image.rows;

	// ÿ���ֽ���
	size_t step = image.step;

	uchar div2 = div >> 1; // div / 2

	for (int i = 0; i < rows; i++)
	{
		// �� i ������
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// ����ÿ�����أ���������
			*data++ = *data / div * div + div2;
		}
	}
}

// λ����
void reduce_color4(cv::Mat image, int div = 64)
{
	// ����
	int rows = image.rows;

	// ÿ���ֽ���
	size_t step = image.step;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

	uchar div2 = div >> 1; // div / 2

	uchar mask = 0xFF << n;

	for (int i = 0; i < rows; i++)
	{
		// �� i ������
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// ����ÿ�����أ���������
			data[j] &= mask;
			data[j] += div2;

			//*data &= mask;
			//*data++ += div2; // 
		}
	}
}


// λ����
void reduce_color5(cv::Mat image, int div = 64)
{
	// ����
	int rows = image.rows;

	// ÿ���ֽ���
	size_t step = image.step;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

	uchar div2 = div >> 1; // div / 2

	uchar mask = 0xFF << n;

	for (int i = 0; i < rows; i++)
	{
		// �� i ������
		uchar *data = image.ptr<uchar>(i);

		for (int j = 0; j < step; j++)
		{
			// ����ÿ������
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



