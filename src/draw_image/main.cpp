#include <opencv2/opencv.hpp>

#include <cstdlib>

#define WINDOW_WIDTH 600

// 椭圆
void draw_ellipse(cv::Mat img, double angle /* 角度 */)
{
	int thickness = 2; // 线宽
	int line_type = 8; // 线形

	cv::ellipse(img,
			cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
			cv::Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
			angle,      // 旋转角度
			0, 360,     // 扩展弧度
			cv::Scalar(255, 129, 0), // 图形颜色
			thickness,
			line_type);

}

void draw_line(cv::Mat img, cv::Point start, cv::Point end)
{
	int thickness = 2; // 线宽
	int line_type = 8; // 线形

	cv::line(img,
			start, end,
			cv::Scalar(0, 0, 0), // 黑色
			thickness,
			line_type);
}

void draw_filled_circle(cv::Mat img, cv::Point center)
{
	int thickness = -1; // 线宽, 绘制实心圆
	int line_type = 8; // 线形

	cv::circle(img,
			center,
			WINDOW_WIDTH/32,
			cv::Scalar(0, 0, 255), // BGR 红色
			thickness,
			line_type);
}
// 多边形
void draw_polygon(cv::Mat img)
{
	int line_type = 8; // 线形

	cv::Point rook_points[1][5];
	rook_points[0][0] = cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8 * 7);
	rook_points[0][1] = cv::Point(WINDOW_WIDTH / 4 * 3, WINDOW_WIDTH / 8 * 7);
	rook_points[0][2] = cv::Point(WINDOW_WIDTH / 4 * 3, WINDOW_WIDTH / 16 * 13);
	rook_points[0][3] = cv::Point(WINDOW_WIDTH / 4 * 11, WINDOW_WIDTH / 8 * 7);
	rook_points[0][4] = cv::Point(WINDOW_WIDTH / 32 * 19  , WINDOW_WIDTH / 8 * 7);

	const cv::Point *ppt[1] = { rook_points[0] };
	int npt[] = {5};

	cv::fillPoly(img, ppt, npt,
			1, // 绘制一个多边形
			cv::Scalar(255, 255, 255),
			line_type);

}

int main(int argc, char *argv[])
{
	cv::Mat atom_img = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	draw_ellipse(atom_img, 90);
	draw_ellipse(atom_img, 0);
	draw_ellipse(atom_img, 45);
	draw_ellipse(atom_img, -45);

	draw_filled_circle(atom_img, cv::Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	cv::imshow("atom", atom_img);
	cv::moveWindow("atom", 0, 200);

	cv::waitKey(0);

	exit(EXIT_SUCCESS);
}

