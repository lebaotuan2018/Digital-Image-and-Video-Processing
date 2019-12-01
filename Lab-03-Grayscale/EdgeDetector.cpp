#include "EdgeDetector.h"

/*
Hàm phát hiện biên cạnh của ảnh xám
sourceImage: ảnh input
destinationImage: ảnh output
method: phương pháp detect
1: Sobel
2: Prewitt
3: Laplace
Hàm trả về
0: nếu detect thành công
1: nếu detect thất bại (không đọc được ảnh input,...)
*/
int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.rows <= 0 || sourceImage.cols <= 0)
	{
		return 1;
	}
	int n = kWidth*kHeight;
	int column, row;
	column = sourceImage.cols;
	row = sourceImage.rows;

	// Sobel
	if (method == 1)
	{
		Convolution C;
		// Ma trận Gx, Gy
		vector <float> Sx;
		vector <float> Sy;
		for (int i = -kWidth / 2; i < kWidth / 2 + 1; i++)
		{
			for (int j = -kHeight / 2; j < kHeight / 2 + 1; j++)
			{
				if (i == 0 && j == 0)
				{
					Sx.push_back(0);
					Sy.push_back(0);
					continue;
				}
				float sx = (float)(i) / (float)(i*i + j*j);
				Sx.push_back(sx);
				float sy = (float)(j) / (float)(i*i + j*j);
				Sy.push_back(sy);
			}
		}

		// Tìm biên cạnh
		int fi, fj;
		fi = kHeight / 2;
		fj = kWidth / 2;
		for (int i = fi; i < row - fi; i++)
		{

			for (int j = fj; j < column - fj; j++)
			{
				int *temp = new int[n];
				int te = 0;
				for (int ti = 0; ti < kHeight; ti++)
				{
					// Dòng ti
					// Xác định giá trị lùi hay tiến của i với +x hoặc -x
					int x;
					x = -fi + ti;
					for (int tj = 0; tj < kWidth; tj++)
					{
						int y;
						// Xác định giá trị lùi hay tiến của j với +y hoặc -y
						y = -fj + tj;

						//Lưu giá trị các pixel vào mảng theo từng dòng liên tiếp
						temp[te] = (int)(sourceImage.at<uchar>(i + x, j + y));
						te++;
					}
				}
				// Tính tích chập
				float Sum_Sx = 0, Sum_Sy = 0;
				for (int l = 0; l < Sx.size(); l++)
				{
					Sum_Sx += Sx[l] * (float)(temp[l]);
					Sum_Sy += Sy[l] * (float)(temp[l]);
				}

				//Tính giá trị
				float e;
				e = sqrt(pow((float)(Sum_Sx) / 2, 2) + pow((float)(Sum_Sy) / 2, 2));
				int gray = (int)(e + 0.5);
				destinationImage.at<uchar>(i, j) = (unsigned char)(gray);

				delete[]temp;

			} // end vòng for cột

		} // end vòng for hàng

		return 0;
	}

	// Prewitt
	if (method == 2)
	{
		Convolution C;
		// Ma trận Gx, Gy
		vector <float> Gx;
		vector <float> Gy;
		for (int i = -kWidth / 2; i < kWidth / 2 + 1; i++)
		{
			for (int j = -kHeight / 2; j < kHeight / 2 + 1; j++)
			{
				float gx = (float)(i);
				Gx.push_back(gx);
				float gy = (float)(j);
				Gy.push_back(gy);
			}
		}
		
		// Tìm biên cạnh
		int fi, fj;
		fi = kHeight / 2;
		fj = kWidth / 2;
		for (int i = fi; i < row - fi; i++)
		{
		
			for (int j = fj; j < column - fj; j++)
			{
				int *temp = new int[n];
				int te = 0;
				for (int ti = 0; ti < kHeight; ti++)
				{
					// Dòng ti
					// Xác định giá trị lùi hay tiến của i với +x hoặc -x
					int x;
					x = -fi + ti;
					for (int tj = 0; tj < kWidth; tj++)
					{
						int y;
						// Xác định giá trị lùi hay tiến của j với +y hoặc -y
						y = -fj + tj;
		
						//Lưu giá trị các pixel vào mảng theo từng dòng liên tiếp
						temp[te] = (int)(sourceImage.at<uchar>(i + x, j + y));
						te++;
					}
				}
				// Tính tích chập
				float Sum_Gx = 0, Sum_Gy = 0;
				for (int l = 0; l < Gx.size(); l++)
				{
					Sum_Gx += Gx[l] * (float)(temp[l]);
					Sum_Gy += Gy[l] * (float)(temp[l]);
				}
		
				//Tính giá trị
				float e;
				e = sqrt(pow((float)(Sum_Gx) / 3, 2) + pow((float)(Sum_Gy) / 3, 2));
				int gray = (int)(e + 0.5);
				destinationImage.at<uchar>(i, j) = (unsigned char)(gray);
		
				delete[]temp;
		
			} // end vòng for cột
		
		} // end vòng for hàng

		
		return 0;
	}

	// Laplace
	if (method == 3)
	{
		Convolution C;
		vector <float> L(n, 1);
		int vt = n / 2;
		L[vt] = (float)(1 - kHeight*kWidth);
		C.SetKernel(L, kWidth, kHeight);
		C.DoConvolution(sourceImage, destinationImage);
		return 0;
	}

	return 1;
}

EdgeDetector::EdgeDetector()
{
}


EdgeDetector::~EdgeDetector()
{
}
