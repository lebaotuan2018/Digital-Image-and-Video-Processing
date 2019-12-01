#pragma once
#include<iostream>
#include<string>
#include<string.h>
#include<cmath>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 

using namespace cv;
using namespace std;
class Converter
{
	/*
	Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage);


	/*
	Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int GrayScale2RGB(const Mat& sourceImage, Mat& destinationImage);


	

	/*
	Hàm chuyển đổi 1 bộ (pixel) RGB sang HSV
	src_r, src_g, src_b: input (thông số R, G, B của 1 pixel)
	dst_h, dst_s, dst_v: output (thông số H, S, V của 1 pixel)
	*/
	void C_rgb2hsv(const unsigned char &src_r, const unsigned char &src_g, const unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v);

	/*
	Hàm chuyển đổi không gian màu của ảnh từ HSV sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int HSV2RGB(const Mat& sourceImage, Mat& destinationImage);

	/*
	Hàm chuyển đổi 1 bộ (pixel) HSV sang RGB
	dst_h, dst_s, dst_v: input (thông số H, S, V của 1 pixel)
	src_r, src_g, src_b: output (thông số R, G, B của 1 pixel)
	
	*/
	void Converter::hsv2rgb(const unsigned char &src_h, const unsigned char &src_s, const unsigned char &src_v, unsigned char &dst_r, unsigned char &dst_g, unsigned char &dst_b);
public:
	/*
	Hàm chuyển đổi không gian màu của ảnh từ RGB sang HSV
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int RGB2HSV(const Mat& sourceImage, Mat& destinationImage);

	/*
	Hàm chuyển đổi không gian màu của ảnh
	sourceImage: ảnh input
	destinationImage: ảnh output cùng kích thước, cùng loại với ảnh input
	type: loại chuyển đổi
	0,1: chuyển từ RGB sang GrayScale và ngược lại
	2,3: chuyển từ RGB sang HSV và ngược lại
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input hay type không chính xác,...)
	*/
	int Convert(Mat& sourceImage, Mat& destinationImage, int type);
	Converter();
	~Converter();
};

