#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include <string.h>
#include <cmath>

#include "AffineTransform.h"
#include "PixelInterpolate.h"
#include "GeometricTransformer.h"
#include "BilinearInterpolate.h"
#include "NearestNeighborInterpolate.h"


using namespace cv;
using namespace std;

int main(int agrc, char *agrv[])
{
	char s1[] = "--zoom";
	char s2[] = "--rotate";
	char s3[] = "--rotateN";
	char a1[] = "--bl";
	char a2[] = "--nn";
	if (agrc == 5)
	{
		AffineTransform A;
		PixelInterpolate *inter;
		NearestNeighborInterpolate nn;// Láng giềng gần
		BilinearInterpolate bl;// Song tuyến tính

		GeometricTransformer gt;

		Mat image = imread(agrv[3], IMREAD_UNCHANGED);

		// Phóng to, thu nhỏ ảnh 
		if (strcmp(s1, agrv[1]) == 0)
		{
			char* d = agrv[4];
			
			if (d[0] == '-')
			{
				cout << "Nhap sai..." << endl;
				
			}
			else
			{
				
				float S = (float)(atof(agrv[4]));
				if (S == 0)
				{
					cout << "Nhap sai..." << endl;
					return 1;
				}
				Mat dst;
				int nC = image.channels();
				cout << endl << "Doi trong giay lat..." << endl;
				if (nC == 1)
				{
					int x = (int)(image.cols *S + 0.5);
					int y = (int)(image.rows *S + 0.5);
					dst = Mat(y, x, CV_8UC1, Scalar(0));
				}
				if (nC == 3)
				{
					int x = (int)(image.cols *S + 0.5);
					int y = (int)(image.rows *S + 0.5);
					dst = Mat(y, x, CV_8UC3, Scalar(0));
				}
				int n;
				// Song tuyến tính
				if (strcmp(a1, agrv[2]) == 0)
				{
					inter = &bl;
					n = gt.Scale(image, dst, S, S, inter);
				}
				// Láng giềng gần
				if (strcmp(a2, agrv[2]) == 0)
				{
					inter = &nn;
					n = gt.Scale(image, dst, S, S, inter);
				}
				if (n == 0)
				{
					cout << "Loi" << endl;
				}
				else
				{
					imshow("Image", image);
					imshow("Ket qua", dst);
					waitKey(0);
				}

			}
		}

		// Xoay ảnh quanh tâm (bảo toàn nội dung ảnh) 
		if (strcmp(s2, agrv[1]) == 0)
		{
			
			float angle = (float)(atof(agrv[4]));
			Mat dst;
			int nC = image.channels();
			cout << endl << "Doi trong giay lat..." << endl;
			if (nC == 1)
			{
				int x = (int)(image.cols + 0.5);
				int y = (int)(image.rows + 0.5);
				dst = Mat(y, x, CV_8UC1, Scalar(0));
			}
			if (nC == 3)
			{
				int x = (int)(image.cols + 0.5);
				int y = (int)(image.rows + 0.5);
				dst = Mat(y, x, CV_8UC3, Scalar(0));
			}
			int n;
			// Song tuyến tính
			if (strcmp(a1, agrv[2]) == 0)
			{
				inter = &bl;
				n = gt.RotateKeepImage(image, dst, angle, inter);
			}
			// Láng giềng gần
			if (strcmp(a2, agrv[2]) == 0)
			{
				inter = &nn;
				n = gt.RotateKeepImage(image, dst, angle, inter);
			}
			if (n == 0)
			{
				cout << "Loi" << endl;
			}
			else
			{
				imshow("Ket qua", dst);
				waitKey(0);
			}

		}

		// Xoay ảnh quanh tâm (không bảo toàn nội dung ảnh) 
		if (strcmp(s3, agrv[1]) == 0)
		{
			float angle = (float)(atof(agrv[4]));

			Mat dst;
			int nC = image.channels();
			cout << endl << "Doi trong giay lat..." << endl;
			if (nC == 1)
			{
				int x = (int)(image.cols + 0.5);
				int y = (int)(image.rows + 0.5);
				dst = Mat(y, x, CV_8UC1, Scalar(0));
			}
			if (nC == 3)
			{
				int x = (int)(image.cols + 0.5);
				int y = (int)(image.rows + 0.5);
				dst = Mat(y, x, CV_8UC3, Scalar(0));
			}
			int n;
			// Song tuyến tính
			if (strcmp(a1, agrv[2]) == 0)
			{
				inter = &bl;
				n = gt.RotateUnkeepImage(image, dst, angle, inter);
			}
			// Láng giềng gần
			if (strcmp(a2, agrv[2]) == 0)
			{
				inter = &nn;
				n = gt.RotateUnkeepImage(image, dst, angle, inter);
			}
			if (n == 0)
			{
				cout << "Loi" << endl;
			}
			else
			{
				imshow("Ket qua", dst);
				waitKey(0);
			}
		}
	}
	else
	{
		cout << "Tham so dong lenh nhap sai" << endl;
		cout << "Vui long nhap lai..." << endl;
	}
	
	return 0;
}