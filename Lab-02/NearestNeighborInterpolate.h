#pragma once
#include "PixelInterpolate.h"


/*
Lớp nội suy màu theo phương pháp láng giềng gần nhất
*/
class NearestNeighborInterpolate : public PixelInterpolate
{
public:
	void Interpolate(
		float tx, float ty,
		uchar* pSrc, int srcWidthStep, int nChannels,
		uchar* pDstRow);

	NearestNeighborInterpolate();
	~NearestNeighborInterpolate();
};

