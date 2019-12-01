#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include <cmath>

#include "Blur.h"
#include "Convolution.h"
#include "EdgeDetector.h"


using namespace cv;
using namespace std;

int main(int agrc, char *agrv[])
{
	char s1[] = "--mean";
	char s2[] = "--median";
	char s3[] = "--gauss";
	char s4[] = "--sobel";
	char s5[] = "--prewitt";
	char s6[] = "--laplace";

	if (agrc == 4)
	{
		
		Mat image = imread(agrv[2], CV_LOAD_IMAGE_GRAYSCALE);
		imshow("Image", image);
		Blur B;
		EdgeDetector E;
		char* d = agrv[3];
		int n = 0;
		for (int i = 0; i < strlen(d); i++)
		{
			if (d[i] == 'x')
			{
				break;
			}
			else
			{
				char c = d[i];
				int t = (int)(c - 48);
				n = n * 10 + t;
			}
		}

		if (n == 0)
		{
			return 1;
		}
		if (n > image.rows || n > image.cols)
		{
			cout << "Anh nay khong chuyen duoc..." << endl;
			return 1;
		}

		// Lọc trung bình 
		if (strcmp(s1, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = B.BlurImage(image, dest, n, n, 0);
			if (check == 0)
			{
				imshow("Ket Qua Loc Trung Binh", dest);
			}
			else
			{
				cout << "Loc anh that bai..." << endl;
			}

			waitKey(0);
		}
		// Lọc trung vị
		if (strcmp(s2, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = B.BlurImage(image, dest, n, n, 1);
			if (check == 0)
			{
				imshow("Ket Qua Loc Trung Vi", dest);
			}
			else
			{
				cout << "Loc anh that bai..." << endl;
			}
			

			waitKey(0);
		}
		
		// Lọc gaussian
		if (strcmp(s3, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = B.BlurImage(image, dest, n, n, 2);
			if (check == 0)
			{
				imshow("Ket Qua Loc Gaussian", dest);
			}
			else
			{
				cout << "Loc anh that bai..." << endl;
			}
			

			waitKey(0);
		}

		// Phát hiện biên cạnh bằng Sobel
		if (strcmp(s4, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = E.DetectEdge(image, dest, n, n, 1);
			if (check == 0)
			{
				imshow("Ket Qua Sobel", dest);
			}
			else
			{
				cout << "Phat hien bien canh that bai" << endl;
			}
			

			waitKey(0);
		}

		// Phát hiện biên cạnh bằng Prewitt
		if (strcmp(s5, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = E.DetectEdge(image, dest, n, n, 2);
			if (check == 0)
			{
				imshow("Ket Qua Loc Prewitt", dest);
			}
			else
			{
				cout << "Phat hien bien canh that bai" << endl;
			}
			
			waitKey(0);
		}

		// Phát hiện biên cạnh bằng Laplace
		if (strcmp(s6, agrv[1]) == 0)
		{
			int check;
			Mat dest = Mat(image.rows, image.cols, CV_8UC1, Scalar(0));
			check = E.DetectEdge(image, dest, n, n, 3);
			if (check == 0)
			{
				imshow("Ket Qua Loc Laplace", dest);
			}
			else
			{
				cout << "Phat hien bien canh that bai" << endl;
			}
			

			waitKey(0);
		}
	}
	else
	{
		cout << "Tham so dong lenh nhap sai" << endl;
		cout << "Vui long nhap lai..." << endl;
	}

	return 0;
}
