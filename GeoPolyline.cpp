#include "stdafx.h"
#include "GeoPolyline.h"
#include <math.h>


CGeoPolyline::CGeoPolyline(void)
{
}


CGeoPolyline::~CGeoPolyline(void)
{
}


void CGeoPolyline::addPoint(CPoint pt)
{
	pts.Add(pt);
}


/*int CGeoPolyline::getSize(void)
{
return 0;
}*/


// 裁切绘制
void CGeoPolyline::draw(CDC* pDC)
{	

	CPen pen(PS_SOLID, this->lineWidth, RGB(r,g,b));
	pDC->SelectObject(&pen);//保存原始的CPen
	if(clipPts.GetSize()!=0){
		//pDC->PolyBezier(&clipPts[0],clipPts.GetSize()/3*3-2);
		int size = clipPts.GetSize();
		for(int i=0;i<size;i++)
		{
			if(i==0)
				pDC->MoveTo(clipPts[i]);
			else
				pDC->LineTo(clipPts[i]);
		}

	}
	else{
		//pDC->PolyBezier(&pts[0],pts.GetSize()/3*3-2);
		int size = pts.GetSize();
		for(int i=0;i<size;i++)
		{
			if(i==0)
				pDC->MoveTo(pts[i]);
			else
				pDC->LineTo(pts[i]);
		}

	}
}

/*
// 绘制贝塞尔
void CGeoPolyline::draw(CDC* pDC)
{	

	CPen pen(PS_SOLID, this->lineWidth, RGB(r,g,b));
	pDC->SelectObject(&pen);//保存原始的CPen
	if(pts.GetSize()>4){
		//pDC->PolyBezier(&clipPts[0],clipPts.GetSize()/3*3-2);
		int size = pts.GetSize();
		for(int i=0;i<size-3;i++)
		{
			drawBezier(pDC,pts[i],pts[i+1],pts[i+2],pts[i+3]);
		}

	}
	else{
		//pDC->PolyBezier(&pts[0],pts.GetSize()/3*3-2);
		int size = pts.GetSize();
		for(int i=0;i<size;i++)
		{
			if(i==0)
				pDC->MoveTo(pts[i]);
			else
				pDC->LineTo(pts[i]);
		}

	}
}
*/

// 插值处理画直线
void CGeoPolyline::drawDDA(CDC* pDC){
	float x = pts[0].x;
	float y = pts[0].y;
	float dx = pts[1].x-pts[0].x;
	float dy = pts[1].y-pts[0].y;
	int n = abs((int)dx)>abs((int)dy)?abs((int)dx):abs((int)dy);
	dx = dx/n;
	dy = dy/n;
	for(int i=0;i<n;i++){
		pDC->SetPixel(x,y,RGB(255,0,0));
		Sleep(1);
		x = x+dx;
		y = y+dy;
	}
}

/**
*	得到某点所对应的特征码
*/
int CGeoPolyline::getCode(CRect wcRect1,CPoint pt1){
	int code = 0;
	if(pt1.x<wcRect1.left){
		code+=1;
	}
	else if(pt1.x>wcRect1.right)
	{
		code+=2;
	}
	else if(pt1.y<wcRect1.bottom)
	{
		code+=4;
	}
	else if(pt1.y>wcRect1.top){
		code+=8;
	}
	return code;
}

/**
*	裁切
*/
void CGeoPolyline::clipObj(CRect wcRect1){
	clipPts.RemoveAll();
	CPoint pt1,pt2;
	int code1,code2,code;
	int size = pts.GetSize();
	for(int i=0;i<size-1;i++){
		pt1 = pts[i];
		pt2 = pts[i+1];
		code1 = 1;
		code2 = 2;
		code1 = getCode(wcRect1,pt1);
		code2 = getCode(wcRect1,pt2);
		if(code1==0&&code2==0){
			clipPts.Add(pt1);
			clipPts.Add(pt2);
		}
		else if((code1&code2)!=0){
			break;
		}
		else{
			code = code1;
			if(code1==0){
				code = code2;
			}
		}
	}
	if(clipPts.GetSize()>0){
		this->r = 255;
		this->g = 0;
		this->b = 0;
	}
}

/*
*	贝塞尔曲线	
*/
void CGeoPolyline::drawBezier(CDC *pDC,CPoint p0,CPoint p1,CPoint p2,CPoint p3){
	int x,y;
	float t,delt = 0.20;
	float dist = 0.0;
	dist+=sqrt((p0.x-p1.x)*1.0*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y));
	dist+=sqrt((p1.x-p2.x)*1.0*(p1.x-p2.x)+(p0.y-p1.y)*(p0.y-p1.y));
	dist+=sqrt((p2.x-p3.x)*1.0*(p2.x-p3.x)+(p2.y-p3.y)*(p2.y-p3.y));
	dist+=sqrt((p0.x-p3.x)*1.0*(p0.x-p3.x)+(p0.y-p3.y)*(p0.y-p3.y));
	dist = dist/2;
	// 屏幕3个像素所对应的长度
	CSize size1(3,3);
	pDC->DPtoLP(&size1);
	if(dist!=0)
		delt = size1.cx/dist;
	else
		delt = 0.5;
	pDC->MoveTo(p0);
	for(t = delt;t<1.0;t+=delt){
		x = (1-t)*(1-t)*(1-t)*p0.x+3*(1-t)*(1-t)*t*p1.x+3*(1-t)*t*t*p2.x+t*t*t*p3.x;
		y = (1-t)*(1-t)*(1-t)*p0.y+3*(1-t)*(1-t)*t*p1.y+3*(1-t)*t*t*p2.y+t*t*t*p3.y;
		pDC->LineTo(x,y);
	}
	pDC->LineTo(p3);
}
