#pragma once
#include "afxtempl.h"
#include <math.h>
#define M_PI       3.14159265358979323846
class CMapProjection 
{
public:
	CMapProjection(void);
	virtual ~CMapProjection(void);
	float a,e;
	CRect wcRect;
	void getXY(float B, float L, float* x, float* y);
	void getLB(float x, float y, float* L, float* B);
	void draw(CDC* pDC);
};

