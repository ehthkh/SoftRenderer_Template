
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void PutPiexel(const IntPoint& ip);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& ip)
{
	PutPixel(ip.x, ip.y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	/*
	SetColor(255, 0, 0);
	PutPixel(0, 0);

	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	*/

	SetColor(255, 0, 0);

	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	int nradius = (int)radius;

	static float degree = 0;
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix2 rotMat;
	rotMat.SetRotation(degree);

	for (int i = -nradius; i <= nradius; ++i)
	{
		for (int j = -nradius; j <= nradius; ++j)
		{
			PutPiexel(Vector2(i, j) * rotMat);
		}
	}

	/*
	for (int i = 0; i < 640/2; ++i)
	{
		PutPixel(i, 0);
	}
	*/

	Matrix2 scaleMat;
	scaleMat.SetScale(2.0f, 0.5f);

	Matrix2 rotMat;
	rotMat.SetRotation(30.0f);

	Matrix2 srMat = scaleMat * rotMat;
	Matrix2 rsMat = rotMat * scaleMat;

	//원 그리기
	/*
	for (int i = -nradius; i <= nradius; ++i)
	{
		for (int j = -nradius; j <= nradius; ++j)
		{
			IntPoint pt(i, j);
			Vector2 ptVec = pt.ToVector2();
			if (Vector2::DistSquared(center, pt.ToVector2()) <= radius * radius)
			{
				IntPoint scalePt = IntPoint(ptVec * scaleMat);
				PutPixel(scalePt); // pt 원, scalePt 노이즈원
			}
		}
	}
	*/

	//반원 그리기
	/*
	for (int i = -nradius; i <= nradius; ++i)
	{
		for (int j = 0; j <= nradius; ++j)
		{
			IntPoint pt(i, j);
			Vector2 ptVec = pt.ToVector2();
			if (Vector2::DistSquared(center, pt.ToVector2()) <= radius * radius)
			{
				//IntPoint scalePt = IntPoint(ptVec * scaleMat);

				IntPoint rotatedPt(ptVec * rotMat);
				PutPixel(rotatedPt); // pt 원, scalePt 노이즈원
			}
		}
	}
	*/

	/*
	for (int i = -nradius; i <= nradius; ++i)
	{
		for (int j = 0; j <= nradius; ++j)
		{
			IntPoint pt(i, j);
			Vector2 ptVec = pt.ToVector2();
			if (Vector2::DistSquared(center, ptVec) <= radius * radius)
			{
				//IntPoint scalePt = IntPoint(ptVec * scaleMat);

				IntPoint SRPt(ptVec * srMat);
				IntPoint RSPt(ptVec * rsMat);
				PutPixel(RSPt);
			}
		}
	}
	*/


	// Buffer Swap 
	BufferSwap();
}
