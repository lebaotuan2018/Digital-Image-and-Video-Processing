#include "Blur.h"
#define PI 3.1415926535897


/*
Hàm làm trơn ảnh xám
sourceImage: ảnh input
destinationImage: ảnh output
method: phương pháp detect
0: Trung bình
1: Trung vị
2: Gaussian
Hàm trả về
0: nếu detect thành công
1: nếu detect thất bại (không đọc được ảnh input,...)
*/
int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.rows <= 0 || sourceImage.cols <= 0)
	{
		return 1;
	}

	int column, row;
	column = sourceImage.cols;
	row = sourceImage.rows;


	// Lọc Trung bình
	if (method == 0)
	{
		Convolution C;

		// Kích thước mảng
		int n = kHeight*kWidth;
		//Tạo ma trận lọc và lưu vào mảng
		vector<float> TB;

		for (int i = 0; i < n; i++)
		{
			float a = (float)(1) / (float)(n);
			TB.push_back(a);
		}

		C.SetKernel(TB, kWidth, kHeight);

		// Thực hiện biến đổi
		C.DoConvolution(sourceImage, destinationImage);

		return 0;
	}

	// Lọc Trung vị
	if (method == 1)
	{
		// Do lọc trung vị nên không cần thiết tính tích chập

		int n = kWidth*kHeight;
		int fi, fj;
		fi = kHeight / 2;
		fj = kWidth / 2;
		for (int i = 0; i < row; i++)
		{
			
			for (int j = 0; j < column; j++)
			{
				int *temp = new int[n];
				int *temp_r = new int[n];
				int *temp_g = new int[n];
				int *temp_b = new int[n];

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

				if (sourceImage.channels() == 1)
				{
					// Sắp xếp mảng tăng dần 
					// Thuật toán Insertion Sort
					for (int it = 1; it < n; it++)
					{
						int xt = temp[it];
						int jt = it;
						while (jt > 0 && temp[jt - 1] > xt)
						{
							temp[jt] = temp[jt - 1];
							jt--;
						}
						temp[jt] = xt;
					}
					//Giá trị trung vị
					int vt;
					if (i == 0 || j == 0 || i == row - 1 || j == column - 1)
					{
						int cot = 0;
						for (int it = 1; it < n; it++)
						{
							if (temp[it] != 0)
							{
								cot++;
							}
						}
						vt = cot / 2;
					}
					else
					{
						vt = (int)(((float)(n) / 2) + 1);
					}

					int gray = temp[vt];
					// Gán giá trị cho ảnh output
					destinationImage.at<uchar>(i, j) = (unsigned char)(gray);
				}
				else
				{
					// Sắp xếp mảng tăng dần 
					// Thuật toán Insertion Sort
					for (int it = 1; it < n; it++)
					{
						int xt = temp_r[it];
						int jt = it;
						while (jt > 0 && temp_r[jt - 1] > xt)
						{
							temp_r[jt] = temp_r[jt - 1];
							jt--;
						}
						temp_r[jt] = xt;
					}
					for (int it = 1; it < n; it++)
					{
						int xt = temp_b[it];
						int jt = it;
						while (jt > 0 && temp_b[jt - 1] > xt)
						{
							temp_b[jt] = temp_b[jt - 1];
							jt--;
						}
						temp_b[jt] = xt;
					}
					for (int it = 1; it < n; it++)
					{
						int xt = temp_g[it];
						int jt = it;
						while (jt > 0 && temp_g[jt - 1] > xt)
						{
							temp_g[jt] = temp_g[jt - 1];
							jt--;
						}
						temp_g[jt] = xt;
					}
					//Giá trị trung vị
					int vt_r, vt_g, vt_b;

					if (i == 0 || j == 0 || i == row - 1 || j == column - 1)
					{
						int cot_r = 0;
						int cot_b = 0;
						int cot_g = 0;
						for (int it = 1; it < n; it++)
						{
							if (temp_r[it] != 0)
							{
								cot_r++;
							}
							if (temp_g[it] != 0)
							{
								cot_g++;
							}
							if (temp_b[it] != 0)
							{
								cot_b++;
							}
						}
						vt_r = cot_r / 2;
						vt_b = cot_b / 2;
						vt_g = cot_g / 2;
					}
					else
					{
						vt_r = (int)(((float)(n) / 2) + 1);
						vt_g = vt_r;
						vt_b = vt_r;
					}
					int R = temp_r[vt_r];
					int G = temp_g[vt_g];
					int B = temp_b[vt_b];
					destinationImage.at<Vec3b>(i, j)[0] = (unsigned char)(B);
					destinationImage.at<Vec3b>(i, j)[1] = (unsigned char)(G);
					destinationImage.at<Vec3b>(i, j)[2] = (unsigned char)(R);
				}
				delete[]temp;
				delete[]temp_r;
				delete[]temp_g;
				delete[]temp_b;

			} // end vòng for cột

		} // end vòng for hàng
		return 0;

	}

	// Lọc Gaussian
	if (method == 2)
	{
		Convolution C;
		// Kích thước mảng
		int n = kHeight*kWidth;

		//Tạo ma trận lọc cho Gaussian
		vector<float> G;
		// Độ lệch chuẩn của hàm Gaussian
		float sigma = 1;
		float in_Sqrt2Pi_Sigma;
		float in_2_SigmaSquare;
		int indRow, indCol;
		in_Sqrt2Pi_Sigma = (float)(1 / (sqrt(2 * PI) * sigma));
		in_2_SigmaSquare = 1 / (2 * sigma * sigma);

		for (indRow = -kHeight / 2; indRow < ((kHeight - 1) / 2) + 1; indRow++)
		{
			for (indCol = -kWidth / 2; indCol < ((kWidth - 1) / 2) + 1; indCol++)
			{
				G.push_back(in_Sqrt2Pi_Sigma* exp(-(indRow*indRow + indCol*indCol)*in_2_SigmaSquare));
			}
		}

		// Tính tổng của ma tran trận kernel Gaussian
		float sumdKer = 0;
		for (int si = 0; si < G.size(); si++)
		{
			sumdKer += G[si];
		}
		if (sumdKer == 0)
		{
			sumdKer = 1;
		}
		// Chuẩn hóa lại ma trận guassian
		for (int si = 0; si < G.size(); si++)
		{
			float m = G[si] / sumdKer;
			G[si] = m;
		}

		C.SetKernel(G, kWidth, kHeight);

		// Thực hiện biến đổi
		C.DoConvolution(sourceImage, destinationImage);
		return 0;
	}
	return 1;
}



Blur::Blur()
{
}


Blur::~Blur()
{
}
