#pragma once
#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include <cmath>

using namespace cv;
using namespace std;

/*
Lớp base dùng để nội suy màu của 1 pixel
*/
class PixelInterpolate
{
public:
	/*
	Hàm tính giá trị màu của ảnh kết quả từ nội suy màu trong ảnh gốc và gán màu được nội suy trong ảnh kết quả
	Tham số
	- (tx,ty): tọa độ thực của ảnh gốc sau khi thực hiện phép biến đổi affine
	- pSrc: con trỏ ảnh gốc
	- srcWidthStep: widthstep của ảnh gốc
	- nChannels: số kênh màu của ảnh gốc
	- pDstRow: con trỏ của ảnh kết quả đến pixel đang muốn nội suy màu

	*/
	virtual void Interpolate(
		float tx, float ty,
		uchar* pSrc, int srcWidthStep, int nChannels,
		uchar* pDstRow) = 0;
	PixelInterpolate();
	~PixelInterpolate();
};

