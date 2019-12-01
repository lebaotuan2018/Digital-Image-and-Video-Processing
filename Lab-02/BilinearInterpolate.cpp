#include "BilinearInterpolate.h"

void BilinearInterpolate::Interpolate(float tx, float ty, uchar* pSrc, int srcWidthStep, int nChannels, uchar* pDstRow)
{

	// Tìm lân cận xung quanh nó
	int sx, sy;

	sx = (int)(tx);// tx = 0.8 -> sx = 0 (làm tròn xuống)
	sy = (int)(ty);// ty = 0.8 -> sy = 0

	float dx, dy;
	dx = tx - sx; // số dư
	dy = ty - sy;

	// tx và tx là số nguyên
	if (dx == 0 && dy == 0)
	{
		// xx là hàng , yy là cột.
		int x = sx, y = sy;
		int column = srcWidthStep / nChannels;

		// Xử lý ảnh xám
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
		
		// Xử lý ảnh màu
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
	else
	{
		// Mảng lưu vị trí điểm
		int *A = new int[8];
		// tx và ty đều là số thực

		if (dx != 0 && dy != 0)
		{
			// Trường hợp này chỉ cần tìm 4 điểm
			// Mảng lưu vị trí lân cận
			// x1,...,xn,y1,...,yn 

			A[0] = sx;
			A[1] = sx + 1;
			A[2] = sx + 1;
			A[3] = sx;

			A[4] = sy;
			A[5] = sy;
			A[6] = sy + 1;
			A[7] = sy + 1;

		}

		// tx là số nguyên, ty là số thực
		if (dx == 0 && dy != 0)
		{
			// Tìm 4 điểm quanh nó
			// Mảng lưu vị trí lân cận
			// x1,...,xn,y1,...,yn 
			if (sx == 0)
			{
				// Lấy các điểm về phía bên phải x = 0
				A[0] = sx;
				A[1] = sx + 1;
				A[2] = sx + 1;
				A[3] = sx;

				A[4] = sy;
				A[5] = sy;
				A[6] = sy + 1;
				A[7] = sy + 1;
			}
			else
			{
				// sx != 0  
				// Lấy các điểm về phía bên trái sx
				A[0] = sx;
				A[1] = sx;
				A[2] = sx - 1;
				A[3] = sx - 1;

				A[4] = sy;
				A[5] = sy + 1;
				A[6] = sy + 1;
				A[7] = sy;
			}


		}

		//tx là số thực và ty là số nguyên
		if (dx != 0 && dy == 0)
		{
			// Tìm 4 điểm quanh nó
			// Mảng lưu vị trí lân cận
			// x1,...,xn,y1,...,yn 

			if (sy == 0)
			{
				// Lấy các điểm về phía bên phải y = 0
				A[0] = sx;
				A[1] = sx + 1;
				A[2] = sx + 1;
				A[3] = sx;

				A[4] = sy;
				A[5] = sy;
				A[6] = sy + 1;
				A[7] = sy + 1;
			}
			else
			{
				// sy != 0  
				// Lấy các điểm về phía bên trái sx
				A[0] = sx;
				A[1] = sx;
				A[2] = sx + 1;
				A[3] = sx + 1;

				A[4] = sy;
				A[5] = sy - 1;
				A[6] = sy - 1;
				A[7] = sy;
			}

		}

		// Nội suy màu

		int x = sx;
		int y = sy;
		if (sx == 0)
		{
			x = sx + 1;
		}
		if (sy == 0)
		{
			y = sy + 1;
		}

		int column = srcWidthStep / nChannels;
		// Xử lý ảnh xám
		if (nChannels == 1)
		{
			// Biến lưu tổng giá trị của các điểm lân cận theo từng màu.
			int Sum_gr = 0;

			for (int i = 0; i <= y; i++, pSrc += srcWidthStep)
			{

				if (i == A[4] || i == A[5] || i == A[6] || i == A[7])
				{
					// Lấy con trỏ đầu mổi dòng
					uchar* pRow = pSrc;
					for (int j = 0; j < column; j++, pRow += nChannels)
					{

						if (j == A[0] )
						{
							Sum_gr = Sum_gr + int(pRow[0]);
						}

						if (j == A[1])
						{
							Sum_gr = Sum_gr + int(pRow[0]);
						}
						if (j == A[2])
						{
							Sum_gr = Sum_gr + int(pRow[0]);
						}
						if (j == A[3])
						{
							Sum_gr = Sum_gr + int(pRow[0]);
						}

					}

				}

			}

			// Gán giá trị màu
			int r, g, b;
			/*float temp;
			temp = Sum_gr / 4;
			g = (int)(0.5 + temp);*/

			float temp;

			temp = Sum_gr / 4;
			g = (int)(temp);

			pDstRow[0] = (unsigned char)(g);
		
		}

		// Xử lý ảnh màu
		if (nChannels == 3)
		{
			// Biến lưu tổng giá trị của các điểm lân cận theo từng màu.
			int Sum_r = 0, Sum_g = 0, Sum_b = 0;

			for (int i = 0; i <= y; i++, pSrc += srcWidthStep)
			{

				if (i == A[4] || i == A[5] || i == A[6] || i == A[7])
				{
					// Lấy con trỏ đầu mổi dòng
					uchar* pRow = pSrc;
					for (int j = 0; j < column; j++, pRow += nChannels)
					{

						if (j == A[0])
						{
							Sum_r = Sum_r + int(pRow[2]);
							Sum_g = Sum_g + int(pRow[1]);
							Sum_b = Sum_b + int(pRow[0]);
						}

						if (j == A[1])
						{
							Sum_r = Sum_r + int(pRow[2]);
							Sum_g = Sum_g + int(pRow[1]);
							Sum_b = Sum_b + int(pRow[0]);
						}
						if (j == A[2] )
						{
							Sum_r = Sum_r + int(pRow[2]);
							Sum_g = Sum_g + int(pRow[1]);
							Sum_b = Sum_b + int(pRow[0]);
						}
						if (j == A[3])
						{
							Sum_r = Sum_r + int(pRow[2]);
							Sum_g = Sum_g + int(pRow[1]);
							Sum_b = Sum_b + int(pRow[0]);
						}

					}

				}

			}

			// Gán giá trị màu
			int r, g, b;
			/*float temp;
			temp = Sum_r / 4;
			r = (int)(0.5 + temp);

			temp = Sum_g / 4;
			g = (int)(0.5 + temp);

			temp = Sum_b / 4;
			b = (int)(0.5 + temp);*/

			float temp;
			temp = Sum_r / 4;
			r = (int)(temp);

			temp = Sum_g / 4;
			g = (int)(temp);

			temp = Sum_b / 4;
			b = (int)(temp);

			pDstRow[0] = (unsigned char)(b);
			pDstRow[1] = (unsigned char)(g);
			pDstRow[2] = (unsigned char)(r);
		}

		delete[]A;
	}

}


BilinearInterpolate::BilinearInterpolate()
{
}


BilinearInterpolate::~BilinearInterpolate()
{
}
