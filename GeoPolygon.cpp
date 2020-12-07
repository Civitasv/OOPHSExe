#include "stdafx.h"
#include "GeoPolygon.h"


CGeoPolygon::CGeoPolygon(void)
{
}


CGeoPolygon::~CGeoPolygon(void)
{
}

void CGeoPolygon::addPoint(CPoint pt)
{
	pts.Add(pt);
}


void CGeoPolygon::draw(CDC* pDC)
{
	// 普通方法
	if(this->areaType==0){
		int size = pts.GetSize();
		for(int i=0;i<size;i++)
		{
			if(i==0)
				pDC->MoveTo(pts[i]);
			else
				pDC->LineTo(pts[i]);
		}
	}else{
		int size = pts.GetSize();
		POINT *point = new POINT[size];
		for(int i=0;i<size;i++)
		{
			point[i] = pts[i];
		}
		CBrush brush1(RGB(r2,g2,b2));

		pDC->SelectObject(&brush1);
		pDC->Polygon(point,size);
	}
	
	// 漫水法
	// floodFillPolygon(pDC);
}

void CGeoPolygon::floodFillPolygon(CDC *pDC){
	int size = pts.GetSize();
	for(int i=0;i<size;i++)
	{
		if(i==0)
			pDC->MoveTo(pts[i]);
		else
			pDC->LineTo(pts[i]);
	}
	int x,y;
	CPoint pt;
	while(seeds.GetSize()>0){
		pt = seeds.GetAt(seeds.GetSize()-1);
		x = pt.x;
		y = pt.y;
		pDC->SetPixel(x,y,RGB(r2,g2,b2));
		seeds.RemoveAt(seeds.GetSize()-1);
		if(pDC->GetPixel(x+1,y) == RGB(255,255,255))
			seeds.Add(CPoint(x+1,y));
		if(pDC->GetPixel(x,y+1) == RGB(255,255,255))
			seeds.Add(CPoint(x,y+1));
		if(pDC->GetPixel(x-1,y) == RGB(255,255,255))
			seeds.Add(CPoint(x-1,y));
		if(pDC->GetPixel(x,y-1) == RGB(255,255,255))
			seeds.Add(CPoint(x,y-1));
	}
}