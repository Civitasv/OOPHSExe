#pragma once
#include "geoobject.h"
#include  "afxtempl.h"
class CConvexHull :
	public CGeoObject
{
public:
	CConvexHull(void);
	virtual ~CConvexHull(void);
	// 离散点集坐标串
	CArray<CPoint ,CPoint > pts;
	// 凸壳坐标串
	CArray<CPoint ,CPoint > Chpts;
	// 点集外界矩形
	CRect crWCRect;
	// 设置点集凸壳
	void setConvexHull();
	// 绘制点集和凸壳
	void draw(CDC *pDC);
};

