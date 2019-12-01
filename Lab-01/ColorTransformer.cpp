#include "ColorTransformer.h"
#include "Converter.h"
#define max(a, b, c)  (fmaxf(a, fmaxf(b, c)))



/*
Hàm nhận vào một ảnh, thay đổi độ sáng của ảnh này và lưu kết quả vào ảnh mới
Tham so:
sourceImage	: ảnh ban đầu
destinationImage: ảnh kết quả
b	: giá trị số nguyên dùng để thay đổi độ sáng của ảnh
Hàm trả về:
1: Nếu thành công thì trả về ảnh kết quả (ảnh gốc vẫn giữ nguyên giá trị)
0: Nếu không tạo được ảnh kết quả hoặc ảnh input không tồn tại
*/
int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, uchar b)
{
	if ((sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 0;
	}

	int bright = (int)(b);
	if (sourceImage.channels() == 3)
	{
		CopyImage(sourceImage, destinationImage);

		for (int ir = 0; ir < sourceImage.rows; ir++)
		{
			for (int jc = 0; jc < sourceImage.cols; jc++)
			{
				for (int channel = 0; channel < 3; channel++)
				{
					destinationImage.at<Vec3b>(ir, jc)[channel] = saturate_cast<uchar>(1 * (destinationImage.at<Vec3b>(ir, jc)[channel]) + bright);
				}
			}
		}
	}
	if (sourceImage.channels() == 1)
	{
		CopyImage(sourceImage, destinationImage);
		for (int ir = 0; ir < sourceImage.rows; ir++)
		{
			for (int jc = 0; jc < sourceImage.cols; jc++)
			{
				destinationImage.at<uchar>(ir, jc) = saturate_cast<uchar>(destinationImage.at<uchar>(ir, jc) + bright);
			}
		}
	}
	return 1;
}


/*
Hàm sao chép ảnh
Tham so:
sourceImage	: ảnh ban đầu
destinationImage: ảnh kết quả
*/
void ColorTransformer::CopyImage(const Mat sourceImage, Mat& destinationImage)
{
	if (sourceImage.channels() == 3)
	{
		for (int i = 0; i < sourceImage.rows; i++)
		{
			for (int j = 0; j < sourceImage.cols; j++)
			{
				destinationImage.at<Vec3b>(i, j)[0] = sourceImage.at<Vec3b>(i, j)[0];
				destinationImage.at<Vec3b>(i, j)[1] = sourceImage.at<Vec3b>(i, j)[1];
				destinationImage.at<Vec3b>(i, j)[2] = sourceImage.at<Vec3b>(i, j)[2];
			}
		}
	}
	if (sourceImage.channels() == 1)
	{
		for (int i = 0; i < sourceImage.rows; i++)
		{
			for (int j = 0; j < sourceImage.cols; j++)
			{
				destinationImage.at<uchar>(i, j) = sourceImage.at<uchar>(i, j);

			}
		}
	}
}

/*
Hàm nhận vào một ảnh, thay đổi độ tương phản của ảnh này và lưu kết quả vào ảnh mới
Tham so :
sourceImage : ảnh ban đầu
destinationImage : ảnh kết quả
c	: giá trị số thực dùng để thay đổi độ tương phản của ảnh
Hàm trả về:
1: Nếu thành công thì trả về ảnh kết quả (ảnh gốc vẫn giữ nguyên giá trị)
0: Nếu không tạo được ảnh kết quả hoặc ảnh input không tồn tại
*/
int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c)
{
	if ((sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 0;
	}

	if (sourceImage.channels() == 3)
	{
		CopyImage(sourceImage, destinationImage);
		for (int ir = 0; ir < sourceImage.rows; ir++)
		{
			for (int jc = 0; jc < sourceImage.cols; jc++)
			{
				for (int channel = 0; channel < 3; channel++)
				{
					destinationImage.at<Vec3b>(ir, jc)[channel] = saturate_cast<uchar>(c * (destinationImage.at<Vec3b>(ir, jc)[channel]) + 0);
				}
			}
		}
	}
	if (sourceImage.channels() == 1)
	{
		CopyImage(sourceImage, destinationImage);
		for (int ir = 0; ir < sourceImage.rows; ir++)
		{
			for (int jc = 0; jc < sourceImage.cols; jc++)
			{
				destinationImage.at<uchar>(ir, jc) = saturate_cast<uchar>(c * destinationImage.at<uchar>(ir, jc));

			}
		}
	}
	return 1;
}

/*
Hàm tính histogram cho ảnh
Tham so :
sourceImage : ảnh ban đầu có thể là ảnh xám hoặc ảnh màu
histogram : histogram kết quả của ảnh input.
Nếu input là ảnh xám, histogram chỉ có 1 kênh
Nếu input là ảnh màu, histogram có 3 kênh tương ứng theo 3 kênh của ảnh màu
Hàm trả về:
1: Nếu thành công thì trả về ảnh kết quả (ảnh gốc vẫn giữ nguyên giá trị)
0: Nếu không tạo được ảnh kết quả hoặc ảnh input không tồn tại
*/
int ColorTransformer::CalcHistogram(const Mat& sourceImage, int Cr[], int Cg[], int Cb[])
{
	if ((sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 0;
	}
	if (sourceImage.channels() == 3)
	{
		int temp;
		for (int i = 0; i < sourceImage.rows; i++)
		{
			for (int j = 0; j < sourceImage.cols; j++)
			{
				temp = 0;
				unsigned char r, g, b;
				r = sourceImage.at<Vec3b>(i, j)[2];
				g = sourceImage.at<Vec3b>(i, j)[1];
				b = sourceImage.at<Vec3b>(i, j)[0];

				for (int z = 0; z < 256; z++)
				{
					if ((int)(r) == z)
					{
						Cr[z]++;
						temp++;
					}
					if ((int)(g) == z)
					{
						Cg[z]++;
						temp++;
					}
					if ((int)(b) == z)
					{
						Cb[z]++;
					}
					if (temp == 3)
					{
						z = 255;
					}
				}
			}
		}
	}

	if (sourceImage.channels() == 1)
	{
		for (int i = 0; i < sourceImage.rows; i++)
		{
			for (int j = 0; j < sourceImage.cols; j++)
			{
				unsigned char g;
				g = sourceImage.at<uchar>(i, j);
				for (int z = 0; z < 256; z++)
				{
					if ((int)(g) == z)
					{
						Cg[z]++;
					}
				}
			}
		}
	}
	return 1;
}


/*
Hàm tính histogram cho ảnh
Tham so :
sourceImage : ảnh ban đầu có thể là ảnh xám hoặc ảnh màu
histImage: ảnh histogram
Nếu input là ảnh xám, chỉ vẽ 1 histogram
Nếu input là ảnh màu, vẽ 3 histogram trên cùng 1 ảnh với màu tương ứng
+ histogram của kênh Red vẽ bằng màu đỏ
+ histogram của kênh Green vẽ bằng màu xanh lá
+ histogram của kênh Blue vẽ bằng màu xanh dương
Hàm trả về:
1: Nếu thành công thì trả về ảnh kết quả (ảnh gốc vẫn giữ nguyên giá trị)
0: Nếu không tạo được ảnh kết quả hoặc ảnh input không tồn tại
*/
int ColorTransformer::DrawHistogram(const Mat& sourceImage, Mat& histImage)
{
	if ((sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 0;
	}
	int Cr[256] = { 0 };
	int Cg[256] = { 0 };
	int Cb[256] = { 0 };
	if (sourceImage.channels() == 3)
	{

		int temp = 0;
		int k = CalcHistogram(sourceImage, Cr, Cg, Cb);
		for (int i = 0; i < 256; i++)
		{
			Cr[i] = Cr[i] / 10;
			Cg[i] = Cg[i] / 10;
			Cb[i] = Cb[i] / 10;
		}

		int maxr = MaxArray(Cr, 256);
		int maxg = MaxArray(Cg, 256);
		int maxb = MaxArray(Cb, 256);
		int a = (int)max((float)maxr, (float)maxg, (float)maxb);
		Mat  des = Mat(a + 50, 800, CV_8UC3, Scalar(0));

		int m = a + 49;
		for (int i = 0; i < 256; i++)
		{
			Cr[i] = m - Cr[i];
			Cg[i] = m - Cg[i];
			Cb[i] = m - Cb[i];

		}

		for (int i = 0; i < 256; i++)
		{
			for (int j = Cg[i]; j <= m; j++)
			{
				des.at<Vec3b>(j, i)[0] = 0;//blue
				des.at<Vec3b>(j, i)[1] = 255;//green
				des.at<Vec3b>(j, i)[2] = 0;//red

			}
		}
		for (int i = 256; i < 512; i++)
		{
			int c = (i - 256);
			for (int j = Cr[c]; j <= m; j++)
			{
				des.at<Vec3b>(j, i)[0] = 0;//blue
				des.at<Vec3b>(j, i)[1] = 0;//green
				des.at<Vec3b>(j, i)[2] = 255;//red

			}
		}
		for (int i = 512; i < 768; i++)
		{
			int c = (i - 512);
			for (int j = Cb[c]; j <= m; j++)
			{
				des.at<Vec3b>(j, i)[0] = 255;//blue
				des.at<Vec3b>(j, i)[1] = 0;//green
				des.at<Vec3b>(j, i)[2] = 0;//red

			}
		}
		histImage = des.clone();
	}

	if (sourceImage.channels() == 1)
	{

		int k = CalcHistogram(sourceImage, Cr, Cg, Cb);
		for (int i = 0; i < 256; i++)
		{
			Cg[i] = Cg[i] / 10;
		}

		int maxg = MaxArray(Cg, 256);
		Mat  des = Mat(maxg + 50, 500, CV_8UC3, Scalar(0));

		int m = maxg + 49;
		for (int i = 0; i < 256; i++)
		{
			Cg[i] = m - Cg[i];
		}

		for (int i = 0; i < 768; i += 3)
		{
			for (int j = Cg[i / 3]; j <= m; j++)
			{
				des.at<uchar>(j, i) = 255;
				des.at<uchar>(j, i + 1) = 255;
				des.at<uchar>(j, i + 2) = 255;
			}
		}

		histImage = des.clone();
	}
	return 1;
}

/*
Hàm tìm giá trị lớn nhất của mảng
Tham số:
a[] và n: mảng đầu vào và số phần tử.
Hàm trả về: Giá trị lớn nhất của mảng
*/
int ColorTransformer::MaxArray(int a[], int n)
{
	int Max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > Max)
		{
			Max = a[i];
		}
	}
	return Max;
}


/*
Hàm cân bằng lược đồ màu tổng quát cho ảnh bất kỳ
Tham so :
sourceImage : ảnh ban đầu
destinationImage : ảnh kết quả
Hàm trả về:
1: Nếu thành công thì trả về ảnh kết quả (ảnh gốc vẫn giữ nguyên giá trị)
0: Nếu không tạo được ảnh kết quả hoặc ảnh input không tồn tại
*/
int ColorTransformer::HistogramEqualization(const Mat& sourceImage, Mat& destinationImage)
{
	if ((sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 0;
	}
	int Cr[256] = { 0 };
	int Cg[256] = { 0 };
	int Cb[256] = { 0 };
	CopyImage(sourceImage, destinationImage);
	

	if (sourceImage.channels() == 3)
	{
		Converter A;
		int k = A.RGB2HSV(sourceImage, destinationImage);
		int Cv[256] = { 0 };
		for (int i = 0; i < destinationImage.rows; i++)
		{
			for (int j = 0; j < destinationImage.cols; j++)
			{

				unsigned char v;
				v = destinationImage.at<Vec3b>(i, j)[2];
				for (int z = 0; z < 256; z++)
				{
					if ((int)(v) == z)
					{
						Cv[z]++;

					}

				}
			}
		}

		int Sum_Cv = 0;
		for (int i = 0; i < 256; i++)
		{
			Sum_Cv = Sum_Cv + Cv[i];
		}

		int Bv[256] = { 0 };
		int Av = 0;
		for (int i = 0; i < 256; i++)
		{
			Av = Av + Cv[i];
			for (int j = 0; j < i; j++)
			{
				Av = Av + Cv[j];
			}
			Bv[i] = (Av * 255) / Sum_Cv;
			Av = 0;

		}

		for (int i = 0; i < destinationImage.rows; i++)
		{
			for (int j = 0; j < destinationImage.cols; j++)
			{
				unsigned char v;
				v = destinationImage.at<Vec3b>(i, j)[2];

				for (int z = 0; z < 256; z++)
				{

					if ((int)(v) == z)
					{
						destinationImage.at<Vec3b>(i, j)[2] = (unsigned char)(Bv[z]);
					}

				}
			}

		}
		// Do hàm HSV sang RGB của em còn bị lỗi nên em sử dùng hàm trong thư viện
		cvtColor(destinationImage, destinationImage, CV_HSV2BGR);
	}

	if (sourceImage.channels() == 1)
	{
		CalcHistogram(sourceImage, Cr, Cg, Cb);
		int Sum_Cg = 0;
		for (int i = 0; i < 256; i++)
		{
			Sum_Cg = Sum_Cg + Cg[i];
		}
		// Tính lại mức xám mới.

		int Bg[256] = { 0 };
		int  Ag = 0;
		for (int i = 0; i < 256; i++)
		{
			Ag = Ag + Cg[i];

			for (int j = 0; j < i; j++)
			{
				Ag = Ag + Cg[j];
			}

			Bg[i] = (Ag * 255) / Sum_Cg;
			Ag = 0;
		}

		for (int i = 0; i < destinationImage.rows; i++)
		{
			for (int j = 0; j < destinationImage.cols; j++)
			{
				unsigned char g;
				g = destinationImage.at<uchar>(i, j);

				for (int z = 0; z < 256; z++)
				{

					if ((int)(g) == z)
					{
						destinationImage.at<uchar>(i, j) = (unsigned char)(Bg[z]);
					}
				}
			}
		}

	}

	return 1;
}


ColorTransformer::ColorTransformer()
{
}


ColorTransformer::~ColorTransformer()
{
}
