#include "stdafx.h"
#include "MapProjection.h"


CMapProjection::CMapProjection(void)
{
}


CMapProjection::~CMapProjection(void)
{
}


void CMapProjection::getXY(float B, float L, float* x, float* y)
{
	*x = L * 20037508.34 / 180;
	*y = log(tan((90 + B) * M_PI / 360))/(M_PI / 180);  
	*y = *y * 20037508.34 / 180;
}


void CMapProjection::getLB(float x, float y, float* L, float* B)
{
}


void CMapProjection::draw(CDC* pDC)
{
	double mapScale = pow(10.0,6);
	float xExtends = float(this->wcRect.Width())/mapScale;
	float yExtends = float(this->wcRect.Height())/mapScale;
	int degree = 5;
	int m = xExtends/degree;
	int n = abs(yExtends/degree);
	int i,j;
	int left = wcRect.left;
	int right = wcRect.right;
	int top = wcRect.top;
	int bottom = wcRect.bottom;
	float x1 = 0,y1,x2,y2;
	CPoint pt1,pt2;
	int xStart = left * 1.0/mapScale/degree;
	int yStart = bottom * 1.0/mapScale/degree;
	CString infoStr;
	for(i=0;i<m+2;i++){
		for(j=0;j<n;j++){
			x1 = (xStart+i)*degree;
			if(i%2==0)
				y1 = (yStart+j+1)*degree;
			else
				y1 = (yStart+n-j)*degree;
			
			getXY(y1,x1,&x2,&y2);
			pt1.x = x2;
			pt1.y = y2;
			if(j==0)
				pDC->MoveTo(pt1);
			else
				pDC->LineTo(pt1);
		}
		infoStr.Format(_T("%d"),int(x1));
		pDC->TextOutW(pt1.x,pt1.y,infoStr);
	}
	for(j=1;j<n+1;j++){
		for(i=0;i<m+2;i++){
			if(j%2==0)
				x1 = (xStart+i)*degree;
			else
				x1 = (xStart+m+1-i)*degree;
			y1 = (yStart+j)*degree;
			getXY(y1,x1,&x2,&y2);
			pt1.x = x2;
			pt1.y = y2;
			if(j==0)
				pDC->MoveTo(pt1);
			else
				pDC->LineTo(pt1);
		}
		infoStr.Format(_T("%d"),int(y1));
		pDC->TextOutW(pt1.x,pt1.y,infoStr);
	}
}
