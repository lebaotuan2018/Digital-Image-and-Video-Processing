#include "Converter.h"
#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))

/*
Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
sourceImage: ảnh input
destinationImage: ảnh output
Hàm trả về
0: nếu chuyển thành công
1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.channels() == 1 || (sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 1;
	}

	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	for (int i = 0; i<rows; i++) 
	{
		for (int j = 0; j<cols; j++) 
		{

			Vec3b ins = sourceImage.at<Vec3b>(i, j);

			int blue = ins.val[0];
			int green = ins.val[1];
			int red = ins.val[2];

			destinationImage.at<uchar>(i, j) = (unsigned char)(blue*0.11 + green*0.59 + red*0.3);

		}
	}
	return 0;
}


/*
Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
sourceImage: ảnh input
destinationImage: ảnh output
Hàm trả về
0: nếu chuyển thành công
1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::GrayScale2RGB(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.channels() == 3 ||(sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 1;
	}

	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{

			unsigned char gray = sourceImage.at<uchar>(i, j);
			int G = (int)(gray);
			float r, g, b;
			r = 0.11 * G;
			g = 0.59 * G;
			b = 0.3 * G;
			float A = r + g + b;
			float B = G - A;

			r = r + B;
			g = g + B;
			b = b + B;

			int dr = 1 + (int)(r);
			int dg = 1 + (int)(g);
			int db = 1 + (int)(b);

			destinationImage.at<Vec3b>(i, j)[0] = (unsigned char)(db);
			destinationImage.at<Vec3b>(i, j)[1] = (unsigned char)(dg);
			destinationImage.at<Vec3b>(i, j)[2] = (unsigned char)(dr);


		}
	}
	return 0;
}



/*
Hàm chuyển đổi không gian màu của ảnh từ RGB sang HSV
sourceImage: ảnh input
destinationImage: ảnh output
Hàm trả về
0: nếu chuyển thành công
1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::RGB2HSV(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.channels() == 1 || (sourceImage.rows == 0 && sourceImage.cols == 0))
	{
		// Chuyển đổi thất bại
		return 1;
	}

	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			Vec3b ins = sourceImage.at<Vec3b>(i, j);

			unsigned char blue = ins.val[0];
			unsigned char green = ins.val[1];
			unsigned char red = ins.val[2];
			unsigned char h, s, v;
			C_rgb2hsv(red, green, blue, h, s, v);
			destinationImage.at<Vec3b>(i, j)[0] = h;
			destinationImage.at<Vec3b>(i, j)[1] = s;
			destinationImage.at<Vec3b>(i, j)[2] = v;
		}
	}
	return 0;
}


/*
Hàm chuyển đổi 1 bộ (pixel) RGB sang HSV
src_r, src_g, src_b: input (thông số R, G, B của 1 pixel)
dst_h, dst_s, dst_v: output (thông số H, S, V của 1 pixel)
*/
void Converter::C_rgb2hsv(const unsigned char &src_r, const unsigned char &src_g, const unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v)
{
	float r = src_r / 255.0f;
	float g = src_g / 255.0f;
	float b = src_b / 255.0f;

	float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

	float max = max_f(r, g, b);
	float min = min_f(r, g, b);
	v = max;

	if (max == 0.0f)
	{
		s = 0;
		h = 0;
	}
	else
	{
		if (max - min == 0.0f)
		{
			s = 0;
			h = 0;
		}
		else
		{
			s = (max - min) / max;

			if (max == r)
			{
				h = 60 * ((g - b) / (max - min)) + 0;
			}
			else
			{
				if (max == g)
				{
					h = 60 * ((b - r) / (max - min)) + 120;
				}
				else
				{
					h = 60 * ((r - g) / (max - min)) + 240;
				}
			}
		}

	}
	if (h < 0)
	{
		h += 360.0f;
	}
	dst_h = (unsigned char)(h / 2);   // dst_h : 0-180									 
	dst_s = (unsigned char)(s * 255); // dst_s : 0-255
	dst_v = (unsigned char)(v * 255); // dst_v : 0-255
}

/*
Hàm chuyển đổi không gian màu của ảnh từ HSV sang RGB
sourceImage: ảnh input
destinationImage: ảnh output
Hàm trả về
0: nếu chuyển thành công
1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::HSV2RGB(const Mat& sourceImage, Mat& destinationImage)
{
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{

			Vec3b intensity = sourceImage.at<Vec3b>(i, j);

			unsigned char h = intensity.val[0];
			unsigned char s = intensity.val[1];
			unsigned char v = intensity.val[2];
			unsigned char r, g, b;
			hsv2rgb(h, s, v, r, g, b);
			destinationImage.at<Vec3b>(i, j)[0] = b;
			destinationImage.at<Vec3b>(i, j)[1] = g;
			destinationImage.at<Vec3b>(i, j)[2] = r;
		}
	}
	return 1;
}

/*
Hàm chuyển đổi 1 bộ (pixel) HSV sang RGB
dst_h, dst_s, dst_v: input (thông số H, S, V của 1 pixel)
src_r, src_g, src_b: output (thông số R, G, B của 1 pixel)

*/
void Converter::hsv2rgb(const unsigned char &src_h, const unsigned char &src_s, const unsigned char &src_v, unsigned char &dst_r, unsigned char &dst_g, unsigned char &dst_b)
{
	float h = src_h *   2.0f; // 0-360
	float s = src_s / 255.0f; // 0.0-1.0
	float v = src_v / 255.0f; // 0.0-1.0

	float r, g, b; // 0.0-1.0
	float c = v*s;
	int H = h / 60;
	float x = c * (1 - abs((H % 2) - 1));

	float m = v - c;
	//float m = 0;
	if (0 <= h && h < 60)
	{
		r = c;
		g = x;
		b = 0;
	}
	if (60 <= h && h < 120)
	{
		r = x;
		g = c;
		b = 0;
	}
	if (120 <= h && h < 180)
	{
		r = 0;
		g = c;
		b = x;
	}
	if (180 <= h && h < 240)
	{
		r = 0;
		g = x;
		b = c;
	}
	if (240 <= h && h < 300)
	{
		r = x;
		g = 0;
		b = c;
	}
	if (300 <= h && h < 360)
	{
		r = c;
		g = 0;
		b = x;
	}
	dst_r = (unsigned char)((r + m) * 255); // dst_r : 0-255
	dst_g = (unsigned char)((g + m) * 255); // dst_r : 0-255
	dst_b = (unsigned char)((b + m) * 255); // dst_r : 0-255
}


/*
Hàm chuyển đổi không gian màu của ảnh
sourceImage: ảnh input
destinationImage: ảnh output cùng kích thước, cùng loại với ảnh input
type: loại chuyển đổi
0,1: chuyển từ RGB sang GrayScale và ngược lại
2,3: chuyển từ RGB sang HSV và ngược lại
Hàm trả về
0: nếu chuyển thành công
1: nếu chuyển thất bại (không đọc được ảnh input hay type không chính xác,...)
*/
int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type)
{
	if (type == 0)
	{
		int re = RGB2GrayScale(sourceImage, destinationImage);
		if (re == 1)
		{
			return 1;
		}
		return 0;
	}

	if (type == 1)
	{
		int re = GrayScale2RGB(sourceImage, destinationImage);
		if (re == 1)
		{
			return 1;
		}
		return 0;
	}
	if (type == 2)
	{
		int re = RGB2HSV(sourceImage, destinationImage);
		if (re == 1)
		{
			return 1;
		}
		return 0;
	}
	if (type == 3)
	{
		int re = HSV2RGB(sourceImage, destinationImage);
		if (re == 1)
		{
			return 1;
		}
		return 0;
	}
}

Converter::Converter()
{
}


Converter::~Converter()
{
}
