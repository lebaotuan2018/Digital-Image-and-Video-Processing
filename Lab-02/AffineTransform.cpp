#include "AffineTransform.h"
#define PI 3.14159265

// xây dựng matrix transform cho phép tịnh tiến theo vector (dx,dy) sau đó nhân với ma trận hiện hành
void AffineTransform::Translate(float dx, float dy)
{
	Mat M = Mat(3, 3, CV_32FC1, Scalar(0));

	M.at<float>(0, 0) = 1;
	M.at<float>(1, 1) = 1;
	M.at<float>(2, 2) = 1;

	M.at<float>(0, 2) = dx;
	M.at<float>(1, 2) = dy;
	if (SumMatrix() == 0)
	{
		_matrixTransform = M;

	}
	else
	{
		_matrixTransform = _matrixTransform * M;
	
	}
}


//xây dựng matrix transform cho phép xoay 1 góc angle quanh gốc tọa độ sau đó nhân với ma trận hiện hành
void AffineTransform::Rotate(float angle)
{
	// Khai báo ma trận số thực
	Mat M = Mat(3, 3, CV_32FC1, Scalar(0));

	double val, b1, b2;
	val = PI / 180;
	b1 = cos(angle*val);
	b2 = sin(angle*val);
	double b3 = -b2;

	int sn = (int)(angle) / 90;
	int sn2 = (int)(angle) % 90;
	int sd = sn % 2;
	if (sd == 1 && sn2 == 0)
	{
		b1 = 0;
	}

	sn2 = (int)(angle) % 180;

	if (sn2 == 0)
	{
		b3 = 0;
		b2 = 0;
	}
	M.at<float>(0, 0) = (float)(b1);
	M.at<float>(0, 1) = (float)(b3);
	M.at<float>(1, 0) = (float)(b2);
	M.at<float>(1, 1) = (float)(b1);

	M.at<float>(2, 2) = 1;

	if (SumMatrix() == 0)
	{
		_matrixTransform = M;

	}
	else
	{
		_matrixTransform = _matrixTransform * M;
		
	}
}


//xây dựng matrix transform cho phép tỉ lệ theo hệ số sau đó nhân với ma trận hiện hành
void AffineTransform::Scale(float sx, float sy)
{
	Mat M = Mat(3, 3, CV_32FC1, Scalar(0));

	M.at<float>(2, 2) = 1;
	M.at<float>(0, 0) = sx;
	M.at<float>(1, 1) = sy;

	if (SumMatrix() == 0)
	{
		_matrixTransform = M;

	}
	else
	{
		_matrixTransform = _matrixTransform * M;
		
	}
}


//transform 1 điểm (x,y) theo matrix transform hiện hành đã có
void AffineTransform::TransformPoint(float &x, float &y)
{
	Mat A = Mat(3, 1, CV_32FC1, Scalar(1));
	A.at<float>(0, 0) = x;
	A.at<float>(1, 0) = y;

	A = _matrixTransform * A;

	x = A.at<float>(0, 0);
	y = A.at<float>(1, 0);

}



// Tính tổng ma trận 
float AffineTransform::SumMatrix()
{
	float Sum = 0;
	for (int i = 0; i < _matrixTransform.rows; i++)
	{
		for (int j = 0; j < _matrixTransform.cols; j++)
		{
			Sum += _matrixTransform.at<float>(i, j);
		}
	}
	return Sum;
}


// Hàm xác định vị trị của một điểm ảnh trong ảnh kết quả tương ứng trên ảnh gốc bằng ma trận tổng quát
void AffineTransform::FindPoint(float &x, float &y)
{
	
	Mat  R = Mat(3, 1, CV_32FC1, Scalar(1));

	R.at<float>(0, 0) = x;
	R.at<float>(1, 0) = y;
	// Tìm lại x, y ban đầu
	R = matrannghichdao*R;
	// Gán giá trị lại cho x, y
	x = R.at<float>(0, 0);
	y = R.at<float>(1, 0);
}


// Hàm tính ma trận nghịch đảo
void AffineTransform::TinhMaTran()
{
	// Tính ma trận
	Mat  Q = Mat(3, 3, CV_32FC1, Scalar(0));

	Q = _matrixTransform;

	// Tìm ma trận C chuyển vị để tính ra Q^-1
	Mat  C = Mat(3, 3, CV_32FC1, Scalar(0));

	float c11, c12, c13, c21, c22, c23, c31, c32, c33;
	c11 = (1)*(Q.at<float>(1, 1)*Q.at<float>(2, 2) - Q.at<float>(2, 1)*Q.at<float>(1, 2));
	c12 = (-1)*(Q.at<float>(1, 0)*Q.at<float>(2, 2) - Q.at<float>(2, 0)*Q.at<float>(1, 2));
	c13 = (1)*(Q.at<float>(1, 0)*Q.at<float>(2, 1) - Q.at<float>(2, 0)*Q.at<float>(1, 1));

	c21 = (-1)*(Q.at<float>(0, 1)*Q.at<float>(2, 2) - Q.at<float>(2, 1)*Q.at<float>(0, 2));
	c22 = (1)*(Q.at<float>(0, 0)*Q.at<float>(2, 2) - Q.at<float>(2, 0)*Q.at<float>(0, 2));
	c23 = (-1)*(Q.at<float>(0, 0)*Q.at<float>(2, 1) - Q.at<float>(2, 0)*Q.at<float>(0, 1));

	c31 = (1)*(Q.at<float>(0, 1)*Q.at<float>(1, 2) - Q.at<float>(1, 1)*Q.at<float>(0, 2));
	c32 = (-1)*(Q.at<float>(0, 0)*Q.at<float>(1, 2) - Q.at<float>(1, 0)*Q.at<float>(0, 2));
	c33 = (1)*(Q.at<float>(0, 0)*Q.at<float>(1, 1) - Q.at<float>(1, 0)*Q.at<float>(0, 1));

	// Chuyển vị ma trận C
	C.at<float>(0, 0) = c11;
	C.at<float>(0, 1) = c21;
	C.at<float>(0, 2) = c31;

	C.at<float>(1, 0) = c12;
	C.at<float>(1, 1) = c22;
	C.at<float>(1, 2) = c32;

	C.at<float>(2, 0) = c13;
	C.at<float>(2, 1) = c23;
	C.at<float>(2, 2) = c33;

	// Tính định thức của ma trận Q
	float DT;
	DT = (Q.at<float>(0, 0)*Q.at<float>(1, 1)* Q.at<float>(2, 2)
		+ Q.at<float>(0, 1)*Q.at<float>(1, 2)*Q.at<float>(2, 0)
		+ Q.at<float>(0, 2)*Q.at<float>(1, 0)*Q.at<float>(2, 1))
		- (Q.at<float>(0, 2)*Q.at<float>(1, 1)*Q.at<float>(2, 0) +
			Q.at<float>(0, 0)*Q.at<float>(1, 2)*Q.at<float>(2, 1) +
			Q.at<float>(0, 1)*Q.at<float>(1, 0)*Q.at<float>(2, 2));

	matrannghichdao = (1 / DT)*C;
}



AffineTransform::AffineTransform()
{
	_matrixTransform = Mat(3, 3, CV_32FC1, Scalar(0));
	matrannghichdao = Mat(3, 3, CV_32FC1, Scalar(0));
}


AffineTransform::~AffineTransform()
{
}
