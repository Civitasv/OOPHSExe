#pragma once
#include "geoobject.h"
class CGeoAnno :
	public CGeoObject
{
public:
	CGeoAnno(void);
	virtual ~CGeoAnno(void);
	CPoint point;
	//int getSize(void);
	void draw(CDC* pDC);
	CString annoName;
};

