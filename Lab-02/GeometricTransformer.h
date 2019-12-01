#pragma once
#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include <cmath>

#include "AffineTransform.h"
#include "PixelInterpolate.h"

using namespace cv;
using namespace std;


/*
Lớp thực hiện phép biến đổi hình học trên ảnh
*/
class GeometricTransformer
{
public:

	/*
	Hàm biến đổi ảnh theo 1 phép biến đổi affine đã có
	Tham số
	- beforeImage: ảnh gốc trước khi transform
	- afterImage: ảnh sau khi thực hiện phép biến đổi affine
	- transformer: phép biến đổi affine
	- interpolator: biến chỉ định phương pháp nội suy màu
	Trả về:
	- 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
	- 1: Nếu biến đổi thành công
	*/
	int Transform(
		const Mat &beforeImage,
		Mat &afterImage,
		AffineTransform* transformer,
		PixelInterpolate* interpolator);

	/*
	Hàm xoay bảo toàn nội dung ảnh theo góc xoay cho trước
	Tham số
	- srcImage: ảnh input
	- dstImage: ảnh sau khi thực hiện phép xoay
	- angle: góc xoay (đơn vị: độ)
	- interpolator: biến chỉ định phương pháp nội suy màu
	Trả về:
	- 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
	- 1: Nếu biến đổi thành công
	*/
	int RotateKeepImage(
		const Mat &srcImage, Mat &dstImage, float angle, PixelInterpolate* interpolator);

	/*
	Hàm xoay không bảo toàn nội dung ảnh theo góc xoay cho trước
	Tham số
	- srcImage: ảnh input
	- dstImage: ảnh sau khi thực hiện phép xoay
	- angle: góc xoay (đơn vị: độ)
	- interpolator: biến chỉ định phương pháp nội suy màu
	Trả về:
	- 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
	- 1: Nếu biến đổi thành công
	*/
	int RotateUnkeepImage(
		const Mat &srcImage, Mat &dstImage, float angle, PixelInterpolate* interpolator);

	/*
	Hàm phóng to, thu nhỏ ảnh theo tỉ lệ cho trước
	Tham số
	- srcImage: ảnh input
	- dstImage: ảnh sau khi thực hiện phép xoay
	- sx, sy: tỉ lệ phóng to, thu nhỏ ảnh
	- interpolator: biến chỉ định phương pháp nội suy màu
	Trả về:
	- 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
	- 1: Nếu biến đổi thành công
	*/
	int Scale(
		const Mat &srcImage,
		Mat &dstImage,
		float sx, float sy,
		PixelInterpolate* interpolator);

	GeometricTransformer();
	~GeometricTransformer();
};

