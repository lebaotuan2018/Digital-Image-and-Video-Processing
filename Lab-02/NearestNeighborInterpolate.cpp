#include "NearestNeighborInterpolate.h"

void NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar* pSrc, int srcWidthStep, int nChannels, uchar* pDstRow)
{
	// Tìm lân cận xung quanh nó
	// Tọa độ nguyên của tx, ty
	int sx, sy;

	sx = (int)(tx);// tx = 0.8 -> sx = 0 
	sy = (int)(ty);// ty = 0.8 -> sy = 0

	float dx, dy;
	dx = tx - sx; //Số dư 
	dy = ty - sy;

	// Vị trí cần tìm
	int x, y;

	// tx và ty đều là số thực
	if (dx != 0 && dy != 0)
	{
		// Trường hợp này chỉ cần tìm 4 điểm
		// Mảng lưu vị trí lân cận
		// x1, x2, y1, y2
		int *A = new int[8];

		A[0] = sx;
		A[1] = sx + 1;
		A[2] = sx + 1;
		A[3] = sx;

		A[4] = sy;
		A[5] = sy;
		A[6] = sy + 1;
		A[7] = sy + 1;

		double t1 = sqrt(pow(tx - A[0], 2) + pow(ty - A[4], 2));
		x = A[0], y = A[4]; // Xác định vị trí pixel nào gần tọa độ tx, ty nhất
		for (int i = 1; i < 4; i++)
		{
			double t2 = sqrt(pow(tx - A[i], 2) + pow(ty - A[i + 4], 2));
			if (t2 < t1)
			{
				x = A[i];
				y = A[i + 4];
				t1 = t2;
			}
		}
		delete[]A;

	}

	// tx là số nguyên, ty là số thực
	if (dx == 0 && dy != 0)
	{
		// Tìm 2 điểm quanh nó
		// Mảng lưu vị trí lân cận
		// x1, x2, y1, y2
		int *A = new int[4];
		A[0] = sx;
		A[1] = sx;
		A[2] = sy;
		A[3] = sy + 1;

		double t1 = sqrt(pow(tx - A[0], 2) + pow(ty - A[2], 2));
		double t2 = sqrt(pow(tx - A[1], 2) + pow(ty - A[3], 2));

		if (t1 > t2)
		{
			x = A[1];
			y = A[3];
		}
		else
		{
			x = A[0];
			y = A[2];
		}
		delete[]A;

	}

	//tx là số thực và ty là số nguyên
	if (dx != 0 && dy == 0)
	{
		// Tìm 2 điểm quanh nó
		// Mảng lưu vị trí lân cận
		// x1, x2, y1, y2
		int *A = new int[4];
		A[0] = sx + 1;
		A[1] = sx;
		A[2] = sy;
		A[3] = sy;


		double t1 = sqrt(pow(tx - A[0], 2) + pow(ty - A[2], 2));
		double t2 = sqrt(pow(tx - A[1], 2) + pow(ty - A[3], 2));

		if (t1 > t2)
		{
			x = A[1];
			y = A[3];
		}
		else
		{
			x = A[0];
			y = A[2];
		}
		delete[]A;

	}

	// tx , ty đều là số nguyên
	if (dx == 0 && dy == 0)
	{
		x = sx;
		y = sy;
	}


	int column = srcWidthStep / nChannels;
	///----------------------------------------------------------
	// Xử lý với ảnh xám
	if (nChannels == 1)
	{
		for (int i = 0; i <= sy; i++, pSrc += srcWidthStep)
		{
			if (i == sy)
			{
				// Lấy con trỏ đầu mổi dòng
				uchar* pRow = pSrc;
				for (int j = 0; j < column; j++, pRow += nChannels)
				{
					if (j == sx)
					{
						pDstRow[0] = pRow[0];//truy xuất pixel (x,y) channel thứ 0
						break;
					}
				}
			}
		}
	}


	///-----------------------------------------------------------
	// Xử lý với ảnh màu
	if (nChannels == 3)
	{
		for (int i = 0; i <= sy; i++, pSrc += srcWidthStep)
		{
			if (i == sy)
			{
				// Lấy con trỏ đầu mổi dòng
				uchar* pRow = pSrc;
				for (int j = 0; j < column; j++, pRow += nChannels)
				{
					if (j == sx)
					{
						pDstRow[0] = pRow[0];//truy xuất pixel (x,y) channel thứ 0 
						pDstRow[1] = pRow[1];//truy xuất pixel (x,y) channel thứ 1
						pDstRow[2] = pRow[2];//truy xuất pixel (x,y) channel thứ 2
						break;
					}
				}
			}
		}
	}
}


NearestNeighborInterpolate::NearestNeighborInterpolate()
{
}


NearestNeighborInterpolate::~NearestNeighborInterpolate()
{
}
