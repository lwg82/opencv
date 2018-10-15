/*
 *   访问像素的三种方法
 *
 *
 */

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>


void color_reduce1(cv::Mat& inputImage, cv::Mat& outputImage, int div)
{
	outputImage = inputImage.clone();

	int row_number = outputImage.rows; // 行数
	int col_number = outputImage.cols * outputImage.channels(); // 列数 × 通道数 = 每行元素个数

	for(int i=0; i<row_number; i++)
	{
		uchar *row_ptr = outputImage.ptr<uchar>(i); // 获取第 i 行地址

		for(int j=0; j<col_number; j++)
		{
			row_ptr[j] = row_ptr[j] / div * div + div / 2;
		}
	}
}


void color_reduce2(cv::Mat& inputImage, cv::Mat& outputImage, int div)
{
	outputImage = inputImage.clone();

	cv::Mat_<cv::Vec3b>::iterator itr_beg = outputImage.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itr_end = outputImage.end<cv::Vec3b>();

	for(; itr_beg != itr_end; ++itr_beg)
	{
		(*itr_beg)[0] = (*itr_beg)[0] / div * div;
		(*itr_beg)[1] = (*itr_beg)[1] / div * div;
		(*itr_beg)[2] = (*itr_beg)[2] / div * div;
	}
}


// 动态地址计算
void color_reduce3(cv::Mat& inputImage, cv::Mat& outputImage, int div)
{
	outputImage = inputImage.clone();

	int row_number = outputImage.rows; // 行数
	int col_number = outputImage.cols; // 列数 × 通道数 = 每行元素个数

	std::cout << row_number << ":" << col_number << std::endl;

	for(int i=0; i<row_number; i++)
		for(int j=0; j<col_number; j++)
		{
			outputImage.at<cv::Vec3b>(i,j)[0] = outputImage.at<cv::Vec3b>(i,j)[0]/div*div;// 蓝色通道
			outputImage.at<cv::Vec3b>(i,j)[1] = outputImage.at<cv::Vec3b>(i,j)[1]/div*div;// 绿色通道
			outputImage.at<cv::Vec3b>(i,j)[2] = outputImage.at<cv::Vec3b>(i,j)[2]/div*div;// 红色通道

		}
}

int main(int argc, char *argv[])
{
	cv::Mat src_img = cv::imread("1.jpg");
	cv::imshow("src", src_img);

	cv::Mat dst_img;
	dst_img.create(src_img.rows, src_img.cols, src_img.type());

	double time0 = static_cast<double>(cv::getTickCount());

	color_reduce3(src_img, dst_img, 32);

	time0 = (static_cast<double>(cv::getTickCount()) - time0) / cv::getTickFrequency();

	std::cout << "count seconds: " << time0 << std::endl;

	cv::imshow("dst", dst_img);
	cv::waitKey(0);

	exit(EXIT_SUCCESS);
}

