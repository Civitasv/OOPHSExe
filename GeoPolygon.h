#pragma once
#include "geoobject.h"
class CGeoPolygon :
	public CGeoObject
{
public:
	CGeoPolygon(void);
	virtual ~CGeoPolygon(void);
	CArray<CPoint ,CPoint > pts;
	void addPoint(CPoint pt);
	//int getSize(void);
	void draw(CDC* pDC);
	void floodFillPolygon(CDC *pDC);
	CArray<CPoint ,CPoint > seeds;
};

