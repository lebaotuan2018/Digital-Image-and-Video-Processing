#include "Converter.h"
#include "ColorTransformer.h"

int Check(const Mat &sourceImage, Mat &destinationImage);

int main(int agrc, char *agrv[])
{
	char s1[] = "--rgb2gray";
	char s2[] = "--gray2rgb";
	char s3[] = "--rgb2hsv";
	char s4[] = "--hsv2rgb";
	char s5[] = "--bright";
	char s6[] = "--contrast";
	char s7[] = "--hist";
	char s8[] = "--equalhist";
	if (agrc == 4 || agrc == 3)
	{
		Mat image;
		if (agrc == 3)
		{
			Converter A;
			ColorTransformer C;
			// Chuyển ảnh màu sang ảnh xám
			if (strcmp(s1, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				Mat gray(image.size(), CV_8UC1);
				namedWindow("Show Image");
				imshow("Show Image", image);
				int re = A.Convert(image, gray, 0);
				if (re == 0)
				{
					imshow("Gray", gray);
					waitKey(0);
				}
				else
				{
					cout << "Chuyen doi that bai...";
				}
			}

			// Chuyển ảnh xám sang ảnh màu
			if (strcmp(s2, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				Mat rgb(image.size(), CV_8UC3);
				namedWindow("Show Image");
				imshow("Show Image", image);

				Mat Cimage(image.size(), CV_8UC1);
				int k = Check(image, Cimage);
				if (k == 1)
				{
					int re = A.Convert(Cimage, rgb, 1);
					if (re == 0)
					{
						imshow("Gray", rgb);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai... !";
					}
				}
				else
				{
					cout << "Chuyen doi that bai...";
				}
				
			}

			// Chuyển ảnh từ hệ màu RGB sang hệ màu HSV
			if (strcmp(s3, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				Mat hsv(image.size(), CV_8UC3);
				namedWindow("Show Image");
				imshow("Show Image", image);
				int re = A.Convert(image, hsv, 2);
				if (re == 0)
				{
					imshow("RGB->HSV", hsv);
					waitKey(0);
				}
				else
				{
					cout << "Chuyen doi that bai...";
				}
			}

			// Chuyển ảnh từ hệ màu HSV sang hệ màu RGB
			if (strcmp(s4, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				Mat rgb(image.size(), CV_8UC3);
				namedWindow("Show Image");
				imshow("Show Image", image);
				int re = A.Convert(image, rgb, 3);
				if (re == 0)
				{
					imshow("RGB->HSV", rgb);
					waitKey(0);
				}
				else
				{
					cout << "Chuyen doi that bai...";
				}
			}
			
			// Vẽ histogram
			if (strcmp(s7, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				namedWindow("Show Image");

				imshow("Show Image", image);

				Mat Cimage(image.size(), CV_8UC1);
				int k = Check(image, Cimage);
				if (k == 1)
				{
					Mat dst;
					int re = C.DrawHistogram(Cimage, dst);
					if (re == 1)
					{
						imshow("Histogram", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
				if (k == 0)
				{
					Mat dst;
					int re = C.DrawHistogram(image, dst);
					if (re == 1)
					{
						imshow("Histogram", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
				
			}
			
			// Cân bằng histogram
			if (strcmp(s8, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				namedWindow("Show Image");

				imshow("Show Image", image);

				Mat Cimage(image.size(), CV_8UC1);
				int k = Check(image, Cimage);

				if (k == 1)
				{
					Mat dst (image.size(), CV_8UC1);
					int re = C.HistogramEqualization(Cimage, dst);
					if (re == 1)
					{
						imshow("Can bang histogram", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
				if (k == 0)
				{
					Mat dst(image.size(), CV_8UC3);
					int re = C.HistogramEqualization(image, dst);
					if (re == 1)
					{
						imshow("Can bang histogram", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
				
				
			}




		}
		else
		{
			ColorTransformer B;
			// Tăng độ sáng của ảnh
			if (strcmp(s5, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				namedWindow("Show Image");
				imshow("Show Image", image);
				

				Mat Cimage(image.size(), CV_8UC1);
				int k = Check(image, Cimage);

				if (k == 0)
				{
					Mat dst(image.size(), CV_8UC3);
					int b = atoi(agrv[3]);
					int re = B.ChangeBrighness(image, dst, b);
					if (re == 1)
					{
						imshow("Anh Tang Giam Do Sang", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
				if (k == 1)
				{
					Mat dst(image.size(), CV_8UC1);
					int b = atoi(agrv[3]);
					int re = B.ChangeBrighness(Cimage, dst, b);
					if (re == 1)
					{
						imshow("Anh Tang Giam Do Sang", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
			}

			// Tăng giảm độ tương phản ảnh
			if (strcmp(s6, agrv[1]) == 0)
			{
				image = imread(agrv[2], CV_LOAD_IMAGE_COLOR);
				namedWindow("Show Image");
				imshow("Show Image", image);

				Mat Cimage(image.size(), CV_8UC1);
				int k = Check(image, Cimage);

				if (k == 0)
				{
					Mat dst(image.size(), CV_8UC3);
					double a = atof(agrv[3]);
					float c = (float)(a);
					int re = B.ChangeBrighness(image, dst, c);
					if (re == 1)
					{
						imshow("Anh Tang Giam Do Tuong Phan", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}

				if (k == 1)
				{
					Mat dst(image.size(), CV_8UC1);
					double a = atof(agrv[3]);
					float c = (float)(a);
					int re = B.ChangeBrighness(Cimage, dst, c);
					if (re == 1)
					{
						imshow("Anh Tang Giam Do Tuong Phan", dst);
						waitKey(0);
					}
					else
					{
						cout << "Chuyen doi that bai...";
					}
				}
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

/*
Hàm kiểm tra ảnh xám
Input: Ảnh sourceImage
Output:
	1: Ảnh xám và ảnh xám destinationImage
	0: Không phải ảnh xám
*/
int Check(const Mat &sourceImage, Mat &destinationImage)
{
	int Cr[256] = { 0 };
	int Cg[256] = { 0 };
	int Cb[256] = { 0 };
	ColorTransformer N;
	int k = N.CalcHistogram(sourceImage, Cr, Cg, Cb);
	int temp = 0;
	for (int i = 0; i < 256; i++)
	{
		if (Cr[i] == Cg[i] && Cg[i] == Cb[i])
		{
			temp++;
		}
	}
	if (temp == 256)
	{
		for (int i = 0; i < sourceImage.rows; i++)
		{
			for (int j = 0; j < sourceImage.cols; j++)
			{
				Vec3b ins = sourceImage.at<Vec3b>(i, j);

				int blue = ins.val[0];
				destinationImage.at<uchar>(i, j) = (unsigned char)(blue);
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}