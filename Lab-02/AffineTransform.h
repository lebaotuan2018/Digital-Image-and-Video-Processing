#pragma once
#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include <cmath>

using namespace cv;
using namespace std;



class AffineTransform
{
	//ma trận 3x3 hiện hành biểu diễn phép biến đổi affine
	Mat _matrixTransform;
public:
	// xây dựng matrix transform cho phép tịnh tiến theo vector (dx,dy) sau đó nhân với ma trận hiện hành
	void Translate(float dx, float dy);

	//xây dựng matrix transform cho phép xoay 1 góc angle quanh gốc tọa độ sau đó nhân với ma trận hiện hành
	void Rotate(float angle);

	//xây dựng matrix transform cho phép tỉ lệ theo hệ số sau đó nhân với ma trận hiện hành
	void Scale(float sx, float sy);

	//transform 1 điểm (x,y) theo matrix transform hiện hành đã có
	void TransformPoint(float &x, float &y);



	// Tính tổng ma trận 
	float SumMatrix();

	// Hàm xác định vị trị của một điểm ảnh trong ảnh kết quả tương ứng trên ảnh gốc bằng ma trận tổng quát
	void FindPoint(float &x, float &y);

	// Ma trận ngịch đảo
	Mat matrannghichdao;
	// Hàm tính ma trận nghịch đảo
	void TinhMaTran();



	AffineTransform();
	~AffineTransform();
};

