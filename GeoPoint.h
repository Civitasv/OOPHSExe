#pragma once
#include "GeoObject.h"

class CGeoPoint : public CGeoObject  
{
public:
	CGeoPoint();
	virtual ~CGeoPoint();
	void setPoint(CPoint pt);
	CPoint getPoint();
	void draw(CDC *pDC);
	// 返回一份副本
	CPoint getPos();
	//运算符重载
	//CGeoPoint operator++(int);
private:
	//点
	CPoint pt;
};

