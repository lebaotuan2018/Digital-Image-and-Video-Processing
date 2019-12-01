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
			int *temp_r = new int[n];
			int *temp_g = new int[n];
			int *temp_b = new int[n];
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
						if (sourceImage.channels() == 1)
						{
							temp[te] = 125;
						}
						else
						{
							temp_r[te] = 125;
							temp_g[te] = 125;
							temp_b[te] = 125;
						}
						
					}
					else
					{
						if (sourceImage.channels() == 1)
						{
							temp[te] = (int)(sourceImage.at<uchar>(ix, jy));
						}
						else
						{
							temp_r[te] = (int)(sourceImage.at<Vec3b>(ix, jy)[2]);
							temp_g[te] = (int)(sourceImage.at<Vec3b>(ix, jy)[1]);
							temp_b[te] = (int)(sourceImage.at<Vec3b>(ix, jy)[0]);
						}
						

					}
					te++;
				}
			}
			// Tính tích chập
			if (sourceImage.channels() == 1)
			{
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
			}
			else
			{
				float Sum_r = 0;
				float Sum_g = 0;
				float Sum_b = 0;
				for (int l = 0; l < _kernel.size(); l++)
				{
					Sum_r += _kernel[l] * (float)(temp_r[l]);
					Sum_g += _kernel[l] * (float)(temp_g[l]);
					Sum_b += _kernel[l] * (float)(temp_b[l]);
				}
				if (Sum_r < 0)
				{
					Sum_r = 0;
				}
				if (Sum_g < 0)
				{
					Sum_g = 0;
				}
				if (Sum_b < 0)
				{
					Sum_b = 0;
				}
				int R = (int)(Sum_r + 0.5);
				int G = (int)(Sum_g + 0.5);
				int B = (int)(Sum_b + 0.5);
				destinationImage.at<Vec3b>(i, j)[0] = (unsigned char)(B);
				destinationImage.at<Vec3b>(i, j)[1] = (unsigned char)(G);
				destinationImage.at<Vec3b>(i, j)[2] = (unsigned char)(R);
			}
			delete[]temp;
			delete[]temp_r;
			delete[]temp_g;
			delete[]temp_b;

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
