#pragma once
#include "GeoObject.h"
#include "afxtempl.h" //模板类头文件
class CGeoPolyline : public CGeoObject  
{
public:
	CArray<CPoint ,CPoint > pts;
	CArray<CPoint ,CPoint > clipPts;
	CGeoPolyline();
	virtual ~CGeoPolyline();
	void addPoint(CPoint pt);
	//int getSize(void);
	void draw(CDC* pDC);
	void drawDDA(CDC* pDC);
	int getCode(CRect wcRect1,CPoint pt1);
	void clipObj(CRect wcRect1);
	void drawBezier(CDC *pDC,CPoint p0,CPoint p1,CPoint p2,CPoint p3);
};
