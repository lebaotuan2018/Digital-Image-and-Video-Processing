#include "GeometricTransformer.h"


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
int GeometricTransformer::Transform(
	const Mat &beforeImage,
	Mat &afterImage,
	AffineTransform* transformer,
	PixelInterpolate* interpolator)
{
	if (beforeImage.rows == 0 && beforeImage.cols == 0)
	{
		return 0;
	}
	// Biến đổi ảnh theo ma trận hiện hành của phép biến đổi affine
	// x, y là vị trí của điểm ảnh gốc
	float x, y;

	int srcColumn = beforeImage.cols;
	int srcRow = beforeImage.rows;

	// Nội suy màu cho ảnh kết quả


	int srcWidthStep = (int)(beforeImage.step[0]);
	int srcChannels = (int)(beforeImage.step[1]);

	int width = afterImage.cols, height = afterImage.rows;

	int widthStep = (int)(afterImage.step[0]);
	int nChannels = (int)(afterImage.step[1]);

	uchar* pData = (uchar*)afterImage.data;
	uchar * srcData = (uchar*)beforeImage.data;
	for (int j = 0; j < height; j++, pData += widthStep)
	{
		y = (float)(j);
		uchar *pRoww = pData;
		for (int i = 0; i < width; i++, pRoww += nChannels)
		{
			float temp = y;
			x = (float)(i);

			transformer->FindPoint(x, y);

			// Vùng trống thì x < 0 hoặc y < 0
			if (x < 0 || y < 0 || x > srcColumn || y>srcRow)
			{

			}
			else
			{				
				interpolator->Interpolate(x, y, srcData, srcWidthStep, srcChannels, pRoww);
			}
			
			y = temp;
		}
	}

	return 1;
}

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
int GeometricTransformer::RotateKeepImage(
	const Mat &srcImage, Mat &dstImage, float angle, PixelInterpolate* interpolator)
{
	if (srcImage.rows == 0 && srcImage.cols == 0)
	{
		return 0;
	}

	AffineTransform *trans = new AffineTransform();
	AffineTransform *A = new AffineTransform();
	// Tọa độ tâm xoay ảnh
	float x, y;
	x = ((float)(srcImage.cols) / (float)(2));
	y = ((float)(srcImage.rows) / (float)(2));
	A->Translate(x, y);
	A->Rotate(angle);
	A->Translate(-x, -y);

	// Tìm kích thước ảnh kết quả
	int maxx, minx, maxy, miny;
	// x1,...,xn,y1,...,yn
	int *D = new int[8];
	D[0] = 0;
	D[1] = dstImage.cols - 1;
	D[2] = dstImage.cols - 1;
	D[3] = 0;

	D[4] = 0;
	D[5] = 0;
	D[6] = dstImage.rows - 1;
	D[7] = dstImage.rows - 1;

	float xx, yy;
	xx = (float)(D[0]);
	yy = (float)(D[4]);
	A->TransformPoint(xx, yy);

	minx = (int)(xx + 0.5);
	maxx = (int)(xx + 0.5);
	miny = (int)(yy + 0.5);
	maxy = (int)(yy + 0.5);

	for (int i = 1; i < 4; i++)
	{
		xx = (float)(D[i]);
		yy = (float)(D[i + 4]);

		A->TransformPoint(xx, yy);

		int nx = (int)(xx + 0.5);
		int ny = (int)(yy + 0.5);

		if (nx < minx)
		{
			minx = nx;
		}
		if (nx > maxx)
		{
			maxx = nx;
		}
		if (ny < miny)
		{
			miny = ny;
		}
		if (ny > maxy)
		{
			maxy = ny;
		}

	}
	delete A;
	// Kích thước ảnh kết quả
	/*int column = abs(maxx) + abs(minx) + 1;
	int row = abs(maxy) + abs(miny) + 1;*/
	int column = abs(maxx - minx) + 1;
	int row = abs(maxy - miny) + 1;
	dstImage = Mat(row, column, CV_8UC3, Scalar(0));

	delete[]D;

	// Thực hiện phép xoay

	float dx = ((float)(dstImage.cols) / (float)(2));
	float dy = ((float)(dstImage.rows) / (float)(2));

	float kx = dx - x;
	float ky = dy - y;

	trans->Translate(dx, dy);
	trans->Rotate(angle);
	trans->Translate(-dx, -dy);
	trans->Translate(kx, ky);
	trans->TinhMaTran();


	Transform(srcImage, dstImage, trans, interpolator);

	delete trans;
	return 1;

}

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
int GeometricTransformer::RotateUnkeepImage(
	const Mat &srcImage, Mat &dstImage, float angle, PixelInterpolate* interpolator)
{
	if (srcImage.rows == 0 && srcImage.cols == 0)
	{
		return 0;
	}

	AffineTransform *trans = new AffineTransform();

	// Tọa độ tâm xoay ảnh
	float x, y;
	x = ((float)(dstImage.cols) / (float)(2));
	y = ((float)(dstImage.rows) / (float)(2));

	trans->Translate(x, y);
	trans->Rotate(angle);
	trans->Translate(-x, -y);
	trans->TinhMaTran();

	Transform(srcImage, dstImage, trans, interpolator);

	delete trans;

	return 1;

}

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
int GeometricTransformer::Scale(
	const Mat &srcImage,
	Mat &dstImage,
	float sx, float sy,
	PixelInterpolate* interpolator)
{
	if (srcImage.rows == 0 && srcImage.cols == 0)
	{
		return 0;
	}

	AffineTransform *trans = new AffineTransform();

	trans->Scale(sx, sy);
	trans->TinhMaTran();

	Transform(srcImage, dstImage, trans, interpolator);

	delete trans;
	return 1;
}





GeometricTransformer::GeometricTransformer()
{
}


GeometricTransformer::~GeometricTransformer()
{
}
