#include "Convolution.h"

//trả về kernel q
vector<float> Convolution::GetKernel()
{
	return _kernel;
}


//set kernel, chiều rộng, chiều dài kernel phải là số lẻ
void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
	_kernelWidth = kWidth;
	_kernelHeight = kHeight;
	int n = kWidth * kHeight;


	for (int i = 0; i < n; i++)
	{
		_kernel.push_back(kernel[i]);
	}
}


/*
Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
sourceImage: ảnh input
destinationImage: ảnh output
Hàm trả về
0: nếu tính thành công
1: nếu tính thất bại (không đọc được ảnh input,...)
*/
int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
	int n = _kernelWidth*_kernelHeight;
	int column, row;
	column = sourceImage.cols;
	row = sourceImage.rows;
	int fi, fj;
	fi = _kernelHeight / 2;
	fj = _kernelWidth / 2;
	for (int i = 0; i < row; i++)
	{

		for (int j = 0; j < column; j++)
		{
			int *temp = new int[n];
			int te = 0;
			for (int ti = 0; ti < _kernelHeight; ti++)
			{
				// Dòng ti
				// Xác định giá trị lùi hay tiến của i với +x hoặc -x
				int x;
				x = -fi + ti;
				for (int tj = 0; tj < _kernelWidth; tj++)
				{
					int y;
					// Xác định giá trị lùi hay tiến của j với +y hoặc -y
					y = -fj + tj;

					//Lưu giá trị các pixel vào mảng theo từng dòng liên tiếp
					int ix, jy;
					ix = i + x;
					jy = j + y;
					if (ix < 0 || ix >= row || jy < 0 || jy >= column)
					{
						temp[te] = 125;
					}
					else
					{
						temp[te] = (int)(sourceImage.at<uchar>(ix, jy));

					}
					te++;
				}
			}
			// Tính tích chập
			float Sum = 0;
			for (int l = 0; l < _kernel.size(); l++)
			{
				Sum += _kernel[l] * (float)(temp[l]);
			}
			if (Sum < 0)
			{
				Sum = 0;
			}
			int gray = (int)(Sum + 0.5);
			destinationImage.at<uchar>(i, j) = (unsigned char)(gray);

			delete[]temp;

		} // end vong for cột

	} // end vòng for hàng
	return 0;

}


Convolution::Convolution()
{
}


Convolution::~Convolution()
{
}
